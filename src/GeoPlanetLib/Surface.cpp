
#include <GeoPlanetLib/Surface.h>

using namespace gp;

Surface::Surface(unsigned int resolution)
{
    this->coordinateSystem = std::make_unique<CoordinateSystem>(resolution);

	unsigned int size = this->coordinateSystem->totalRegionCount();
    this->regions.reserve(this->coordinateSystem->totalRegionCount());
	for (unsigned int i = 0; i < size; ++i) {
		this->regions.push_back(std::make_shared<Region>(i));
	}
}
