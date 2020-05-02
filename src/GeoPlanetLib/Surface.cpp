
#include <GeoPlanetLib/Surface.h>

using namespace gp;

Surface::Surface(unsigned int resolution) : coordinateSystem(
	CoordinateSystem(resolution > Surface::MAX_RESOLUTION 
		? Surface::MAX_RESOLUTION 
		: resolution
	)
) {
	regionInit();
}

Surface::~Surface()
{
	clear();
}

void Surface::clear()
{
	TectonicPlate::removePlatesFromSurface(this);
	plates.clear();
}

void Surface::reset()
{
	clear();
	regionInit();
}

void Surface::regionInit()
{
	unsigned int size = coordinateSystem.getTotalRegionCount();
	this->regions.reserve(size);
	for (RegionID i = 0; i < size; ++i) {
		this->regions.push_back(std::make_shared<Region>(SurfacePosition(coordinateSystem, i)));
	}
}
