
#include <GeoPlanetLib/SurfacePosition.h>

using namespace gp;

FaceID SurfacePosition::getFaceID() const
{
    return coordinateSystem.faceIdFromRegionId(regionId);
}

glm::vec3 SurfacePosition::getGlobal() const
{
    return coordinateSystem.localToGlobalPos({ getFaceID(), getLocal() });
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
