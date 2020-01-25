
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

	float jitterX = (rand_f(jitter) - jitter / 2.0f);
	float jitterY = (rand_f(jitter) - jitter / 2.0f);

	if (getGridCoords().y % 2) { // if odd
		jitterX -= 1.0 / 4.0;
	} else {
		jitterX += 1.0 / 4.0;
	}

	if (jitterX < 0) jitterX = 0;
	else if (jitterX > 1) jitterX  = 1;

	if (getGridCoords().x % 2) { // if odd
		jitterY -= 1.0 / 4.0;
	} else {
		jitterY += 1.0 / 4.0;
	}

	if (jitterY < 0) jitterY = 0;
	else if (jitterY > 1) jitterY  = 1;

    float step = 1.0f / float(_coordinateSystem->getResolution());
	float halfStep = step / 2.0f;
    setLocalPointPosition(vec2(
        halfStep + _gridCoords.x * step + jitterX * step,
        halfStep + _gridCoords.y * step + jitterY * step
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
