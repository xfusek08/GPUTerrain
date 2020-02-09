
#include <GeoPlanetLib/Surface.h>

using namespace gp;

Surface::Surface(unsigned int resolution) : coordinateSystem(CoordinateSystem(resolution))
{
    unsigned int size = coordinateSystem.getTotalRegionCount();

    this->regions.reserve(size);
	for (RegionID i = 0; i < size; ++i) {
		this->regions.push_back(std::make_shared<Region>(SurfacePosition(coordinateSystem, i)));
	}
}
