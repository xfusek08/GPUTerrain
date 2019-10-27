
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
	if (jitter < 0) jitter = 0;
	if (jitter > 1) jitter = 1;
	
    float step = 1.0f / float(_coordinateSystem->getResolution());
	float halfStep = step / 2;
    setLocalPointPosition(vec2(
        _gridCoords.x * step + halfStep + (rand_f(jitter) - 0.5) * step,
        _gridCoords.y * step + halfStep + (rand_f(jitter) - 0.5) * step
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
