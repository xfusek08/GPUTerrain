
#include <GeoPlanetLib/CoordinateSystem.h>

using namespace gp;

CoordinateSystem::CoordinateSystem(unsigned int resolution)
{
    this->resolution = resolution;
}

unsigned int CoordinateSystem::totalRegionCount()
{
    return this->resolution * this->resolution * 6;
}
