
#include <GeoPlanetLib/CoordinateSystem.h>

using namespace gp;

CoordinateSystem::CoordinateSystem(unsigned int resolution) : resolution(resolution)
{
    if (resolution <= 0) {
        throw "CoordinateSystem: invalid resolution value. Resolution must be greater than 0";
    }
}
