
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

void SurfaceRegion::randomizeLocalPoint()
{
    float step = 1.0f / float(_coordinateSystem->getResolution());
    setLocalPointPosition(vec2(
        _gridCoords.x * step + rand_f(step),
        _gridCoords.y * step + rand_f(step)
    ));

    // setLocalPointPosition(vec2(
    //     _gridCoords.x * step + (step / 2),
    //     _gridCoords.y * step + (step / 2)
    // ));
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
