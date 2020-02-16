
#include <GeoPlanetLib/CoordinateSystem.h>

using namespace gp;
using namespace glm;

CoordinateSystem::CoordinateSystem(unsigned int resolution) : resolution(resolution)
{
    if (resolution <= 0) {
        throw "CoordinateSystem: invalid resolution value. Resolution must be greater than 0";
    }
}

FaceID CoordinateSystem::faceIdFromRegionId(RegionID RegionID) const
{
    return FaceID(unsigned int(float(RegionID) / float(resolution * resolution)));
}

vec2 CoordinateSystem::warp(vec2 lCoords) const
{
	auto res = tan(CoordinateSystem::WARP_MAGIC_ANGLE * makeLocal3D(lCoords)) / tan(CoordinateSystem::WARP_MAGIC_ANGLE);
	return makeLocal2D(res);
}

vec2 CoordinateSystem::unwarp(vec2 wlCoords) const
{
    auto res = atan(makeLocal3D(wlCoords) * tan(CoordinateSystem::WARP_MAGIC_ANGLE)) / CoordinateSystem::WARP_MAGIC_ANGLE;
	return makeLocal2D(res);
}

vec3 CoordinateSystem::localToGlobalPos(LocalPosition lPos) const
{
    vec2 wlCoords = warp(lPos.coords);
    vec3 p = makeLocal3D(wlCoords);
    mat3 pt = facePermutationMatrix(lPos.faceId);
    return normalize(pt * p);
}

LocalPosition CoordinateSystem::globalToLocalPos(vec3 gPos) const
{
    FaceID faceId = faceFromGlobalPos(gPos);
    mat3 pt = facePermutationMatrix(faceId);
    vec2 wlCoords = makeLocal2D(gPos * pt);
    vec2 lCoords = unwarp(wlCoords);
    return {faceId, lCoords};
}

LocalPosition CoordinateSystem::gridCoordsToLocalPosition(FaceID faceId, glm::ivec2 gridCoords) const
{
    float halfStep = 0.5f / float(resolution);
    float fullstep = 2 * halfStep;
    return {
        faceId,
        vec2(
            halfStep + float(gridCoords.x) * fullstep,
            halfStep + float(gridCoords.y) * fullstep
        )
    };
}

RegionID CoordinateSystem::localPosToRegion(LocalPosition lPos, glm::vec2 *offsetReference, bool allowWrap) const
{
    // coordinates are within the face
    if (lPos.coords.x >= 0 && lPos.coords.x < 1.0f 
		&& lPos.coords.y >= 0 && lPos.coords.y < 1.0f
	) {
		int x = lPos.coords.x * float(resolution);
		int y = lPos.coords.y * float(resolution);
		RegionID regionId = (lPos.faceId * resolution * resolution) + (resolution * y) + x;

		// compute local offset
		if (offsetReference != nullptr) {
			float step = 1.0f / float(resolution);
			*offsetReference = float(resolution) * vec2(
				lPos.coords.x - (step * x),
				lPos.coords.y - (step * y)
			);
		}
		return regionId;
	}
	
	if (!allowWrap) {
        return INVALID_REGION_ID;
    } 

    lPos = wrapLocalPosition(lPos);
    if (lPos.faceId == FaceID::FACE_INVALID) {
        return INVALID_REGION_ID;
    }

    return localPosToRegion(lPos, offsetReference, false);
}

LocalPosition CoordinateSystem::wrapLocalPosition(LocalPosition lPos) const
{
    // Performs wrap if coords extens the face
	vec3 local3dCoords = makeLocal3D(lPos.coords);

	vec2 faceCoords_clamp = clamp(vec2(local3dCoords), -1.0f, 1.0f);
    vec2 faceCoords_extra = abs(faceCoords_clamp - vec2(local3dCoords));
    float extra_dist = faceCoords_extra.x + faceCoords_extra.y;

    // if coords didn't leave the face
    if (extra_dist == 0.0) {
        return lPos;
    }

    if (min(faceCoords_extra.x, faceCoords_extra.y) > 0) {
        return {}; // double wrap - not allowed
    } else {
        // wrap to neighbor cube face in 3D space
        local3dCoords = vec3(faceCoords_clamp.x, faceCoords_clamp.y, 1 - extra_dist);
		auto pt = facePermutationMatrix(lPos.faceId);
        return globalToLocalPos(pt * local3dCoords);
    }
}

ivec2 CoordinateSystem::regionIdToGridCoords(RegionID regionId) const
{
    return ivec2(
        regionId % resolution,
        unsigned(float(regionId) / float(resolution)) % resolution
    );
}

LocalPosition CoordinateSystem::regionIdToLocalPos(RegionID regionId) const
{
    auto gridCoords = regionIdToGridCoords(regionId);
    float step = 1.0f / float(resolution);
    return {
        faceIdFromRegionId(regionId),
        vec2(
            float(gridCoords.x) * step,
            float(gridCoords.y) * step
        )
    };
}


// private

mat3 CoordinateSystem::facePermutationMatrix(FaceID faceId) const
{
    switch(faceId) {
        case FACE_FRONT: return mat3(
            {1,0,0},
            {0,1,0},
            {0,0,1}
        );

        case FACE_RIGHT: return mat3(
            {0,0,-1},
            {0,1,0},
            {1,0,0}
        );

        case FACE_BACK: return mat3(
            {-1,0,0},
            {0,1,0},
            {0,0,-1}
        );

        case FACE_LEFT: return mat3(
            {0,0,1},
            {0,1,0},
            {-1,0,0}
        );

        case FACE_NORTH: return mat3(
            {1,0,0},
            {0,0,-1},
            {0,1,0}
        );

        case FACE_SOUTH: return mat3(
            {1,0,0},
            {0,0,1},
            {0,-1,0}
        );

        default:
            throw "Cannot get permutation matrix for invalid faceid.";
    }
}

FaceID CoordinateSystem::faceFromGlobalPos(vec3 gPos) const
{
    vec3 absVector = abs(gPos);
    float maxComp = max(max(absVector.x, absVector.y), absVector.z);
    gPos /= maxComp; // normalize vector to surface of cube

    if (gPos.z == 1) {
        return FACE_FRONT;
    } else if (gPos.z == -1) {
        return FACE_BACK;
    } else if (gPos.x == 1) {
        return FACE_RIGHT;
    } else if (gPos.x == -1) {
        return FACE_LEFT;
    } else if (gPos.y == 1) {
        return FACE_NORTH;
    } else if (gPos.y == -1) {
        return FACE_SOUTH;
    }
    return FACE_INVALID;
}

vec3 CoordinateSystem::makeLocal3D(vec2 pos2D) const
{
    pos2D *= 2.0f;
    return vec3(-1.0f + pos2D.x, 1.0f - pos2D.y, 1.0f);
}

vec2 CoordinateSystem::makeLocal2D(vec3 pos3D) const
{
    return vec2(pos3D.x + 1.0f, 1.0 - pos3D.y) / 2.0f;
}
