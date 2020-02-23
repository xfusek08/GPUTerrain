
#include <GeoPlanetLib/SurfacePosition.h>

using namespace gp;

FaceID SurfacePosition::getFaceID() const
{
    return coordinateSystem.faceIdFromRegionId(regionId);
}

glm::vec3 SurfacePosition::getGlobal(bool doWarp) const
{
    return coordinateSystem.localToGlobalPos({ getFaceID(), getLocal() }, doWarp);
}

glm::vec2 SurfacePosition::getLocal() const
{
    auto lPos = coordinateSystem.regionIdToLocalPos(regionId);
    return lPos.coords + (localOffset / float(coordinateSystem.getResolution()));
}

glm::vec2 SurfacePosition::getLocalWarped() const
{
    return coordinateSystem.warp(getLocal());
}

glm::uvec2 SurfacePosition::getFaceGridPosition() const
{
    return coordinateSystem.regionIdToGridCoords(regionId);
}

RegionNeighborhood SurfacePosition::getNeighborhood() const
{
    auto gridCoords = getFaceGridPosition();
    auto faceId = getFaceID();
    return {
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(0, -1)),  // 0 - up
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(-1, -1)), // 1 - upLeft
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(-1, 0)),  // 2 - left
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(-1, 1)),  // 3 - downLeft
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(0, 1)),   // 4 - down
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(1, 1)),   // 5 - downRight
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(1, 0)),   // 6 - right
        coordinateSystem.localPosToRegion(faceId, gridCoords + glm::uvec2(1, -1)),  // 7 - upRight
    };
}


void SurfacePosition::setGlobal(glm::vec3 gPos)
{
    LocalPosition lPos = coordinateSystem.globalToLocalPos(gPos);
    setLocal(lPos.coords, lPos.faceId);
}

void SurfacePosition::setLocal(glm::vec2 lCoords, FaceID faceId)
{
    regionId = coordinateSystem.localPosToRegion({faceId, lCoords}, &localOffset);
}

void SurfacePosition::setLocalWarped(glm::vec2 wlCoords, FaceID faceId)
{
    auto lCoords = coordinateSystem.unwarp(wlCoords);
    setLocal(lCoords, faceId);
}
