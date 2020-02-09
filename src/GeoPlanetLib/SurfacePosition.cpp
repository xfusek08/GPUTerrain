
#include <GeoPlanetLib/SurfacePosition.h>

using namespace gp;

glm::vec3 SurfacePosition::getGlobal() const { return {0,0,0}; }
glm::vec2 SurfacePosition::getLocal() const { return {0,0}; }
glm::vec2 SurfacePosition::getLocalOffset() const { return {0,0}; }
glm::vec2 SurfacePosition::getLocalWarped() const { return {0,0}; }
RegionID SurfacePosition::getRegionID() const { return INVALID_REGION_ID; }
FaceID SurfacePosition::getFaceID() const { return FaceID::FACE_INVALID; }
void SurfacePosition::setGlobal(glm::vec3) {}
void SurfacePosition::setLocal(FaceID faceId, glm::vec2 position) {}
void SurfacePosition::setLocalWarped(FaceID faceId, glm::vec2 warpedPosition) {}
void SurfacePosition::setLocalOffset(RegionID region, glm::vec2 position) {}