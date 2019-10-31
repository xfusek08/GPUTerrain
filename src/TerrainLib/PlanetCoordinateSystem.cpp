
#include <stdexcept>
#include <TerrainLib/PlanetCoordinateSystem.h>

using namespace std;
using namespace tl;
using namespace glm;

vec2 PlanetCoordinateSystem::warp(vec2 coords)
{
	auto res = tan(PlanetCoordinateSystem::WARP_MAGIC_ANGLE * local2dTo3d(coords))/tan(PlanetCoordinateSystem::WARP_MAGIC_ANGLE);
	return local3dTo2d(res);
}

vec2 PlanetCoordinateSystem::unwarp(vec2 coords)
{
    auto res = atan(local2dTo3d(coords) * tan(PlanetCoordinateSystem::WARP_MAGIC_ANGLE))/PlanetCoordinateSystem::WARP_MAGIC_ANGLE;
	return local3dTo2d(res);
}

unsigned int PlanetCoordinateSystem::getTotalRegionCount()
{
    return _resolution * _resolution * 6;
}

FaceID PlanetCoordinateSystem::getFaceIdFromRegionId(RegionID RegionID)
{
    return FaceID(unsigned int(float(RegionID) / float(_resolution * _resolution)));
}

FaceID PlanetCoordinateSystem::getFaceIdFrom3dPosition(vec3 position)
{
    vec3 absVector = abs(position);
    float maxComp = max(max(absVector.x, absVector.y), absVector.z);
    position /= maxComp; // normalize vector to surface of cube

    if (position.z == 1) {
        return FACE_FRONT;
    } else if (position.z == -1) {
        return FACE_BACK;
    } else if (position.x == 1) {
        return FACE_RIGHT;
    } else if (position.x == -1) {
        return FACE_LEFT;
    } else if (position.y == 1) {
        return FACE_NORTH;
    } else if (position.y == -1) {
        return FACE_SOUTH;
    }
    return FACE_INVALID;
}

mat3 PlanetCoordinateSystem::getPermutationMatrixByFaceId(FaceID faceId)
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
        default: throw runtime_error("Cannot get permutation matrix for invalid faceid.");
    }
}


uvec2 PlanetCoordinateSystem::getGridCoordsForId(RegionID RegionID)
{
    return uvec2(
        RegionID % _resolution,
        unsigned(float(RegionID) / float(_resolution)) % _resolution
    );
}

vec3 PlanetCoordinateSystem::local2dTo3d(vec2 local2dCoords)
{
    local2dCoords *= 2.0f;
    return vec3(-1.0f + local2dCoords.x, 1.0f - local2dCoords.y, 1.0f);
}

vec2 PlanetCoordinateSystem::local3dTo2d(vec3 local3dCoords)
{
    vec2 local2d = vec2(local3dCoords.x + 1.0f, 1.0 - local3dCoords.y);
    return local2d / 2.0f;
}

vec3 PlanetCoordinateSystem::localFaceCoordsToGlobal(FaceID faceId, vec2 localCoords)
{
    localCoords = warp(localCoords);
    auto pt = getPermutationMatrixByFaceId(faceId);
    auto p = local2dTo3d(localCoords);
	return pt * p;
}

ivec2 PlanetCoordinateSystem::localFaceCoordsToGridCoords(float x, float y)
{
    return ivec2(
        int(x * float(_resolution)),
        int(y * float(_resolution))
    );
}

RegionID PlanetCoordinateSystem::getRegionOnFace(FaceID faceId, int x, int y)
{
	int res = _resolution;
    // coordinates are within the face
    if (x >= 0 && x < res && y >= 0 && y < res) {
        return (faceId * res * res) + (res * y) + x;
    }
    return INVALID_REGION_ID;
}


RegionID PlanetCoordinateSystem::getRegionIdByGrid(FaceID faceId, ivec2 gridCoords)
{
    RegionID region = getRegionOnFace(faceId, gridCoords);
    if (region == INVALID_REGION_ID) {
		float step = 1.0f / float(_resolution);
        region = getRegionIdByLocalCoords(faceId,
			step / 2.0 + float(gridCoords.x) * step,
			step / 2.0 + float(gridCoords.y) * step
        );
    }
    return region;
}

RegionID PlanetCoordinateSystem::getRegionIdByLocalCoords(FaceID faceId, vec2 localCoords)
{
    // Performs wrap over edges of cube if local coords extens the face
	vec3 local3dCoords = local2dTo3d(localCoords);

	vec2 faceCoords_clamp = clamp(vec2(local3dCoords), -1.0f, 1.0f);
    vec2 faceCoords_extra = abs(faceCoords_clamp - vec2(local3dCoords));
    float extra_dist = faceCoords_extra.x + faceCoords_extra.y;

    if (extra_dist == 0.0) {
        // coords did not leave the face
        return getRegionOnFace(faceId, localCoords);
    }

    if (min(faceCoords_extra.x, faceCoords_extra.y) > 0) {
        return INVALID_REGION_ID; // double wrap - not allowed
    } else {
        // wrap to neighbor cube face in 3D space
        local3dCoords = vec3(faceCoords_clamp.x, faceCoords_clamp.y, 1-extra_dist);
		auto pt = getPermutationMatrixByFaceId(faceId);
		vec3 globalPos3d =  pt * local3dCoords;
        return getRegionIdBy3dPosition(globalPos3d);
    }
}

RegionID PlanetCoordinateSystem::getRegionIdBy3dPosition(vec3 position3D)
{
    FaceID faceId = getFaceIdFrom3dPosition(position3D);
    mat3 permutationMatrix = getPermutationMatrixByFaceId(faceId);
    return getRegionIdByLocalCoords(faceId, unwarp(local3dTo2d(position3D * permutationMatrix)));
}
