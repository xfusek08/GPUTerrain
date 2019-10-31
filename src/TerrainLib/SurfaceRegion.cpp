
#include <TerrainLib/SurfaceRegion.h>
#include <TerrainLib/utils.h>

using namespace tl;
using namespace std;
using namespace glm;

SurfaceRegion::SurfaceRegion(shared_ptr<PlanetCoordinateSystem> coordinateSystem, RegionID id):
	_coordinateSystem(coordinateSystem),
    _id(id)
{
    if (!isInvalid()) {
        _faceId = _coordinateSystem->getFaceIdFromRegionId(_id);
        _gridCoords = _coordinateSystem->getGridCoordsForId(_id);
        randomizeLocalPoint();
        randomizeColor();
    }
}

void SurfaceRegion::randomizeLocalPoint(float jitter)
{
	if (jitter < 0) jitter = 0.0f;
	if (jitter > 1) jitter = 1.0f;

    float step = 1.0f / float(_coordinateSystem->getResolution());
	float halfStep = step / 2.0f;
    setLocalPointPosition(vec2(
        halfStep + _gridCoords.x * step + (rand_f(jitter) - jitter / 2.0f) * step,
        halfStep + _gridCoords.y * step + (rand_f(jitter) - jitter / 2.0f) * step
    ));
}

void SurfaceRegion::randomizeColor()
{
    _color = uvec4(
        rand() % 255,
        rand() % 255,
        rand() % 255,
        0
    );
}
