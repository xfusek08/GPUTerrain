
#include <random>

#include <GeoPlanetLib/modifiers/TectonicPlateModifier.h>

#include <GeoPlanetLib/modifiers/ElevationModifier.h>

using namespace gp;
using namespace gp::modifiers;
using namespace std;

bool ElevationModifier::apply(std::shared_ptr<Surface> surface)
{
    for (auto region : surface->getRegions()) {
        auto plate = TectonicPlate::getPlateOfRegion(region);
        if (plate != nullptr) {
            RegionAttributeData data;
            data.scalar = plate->elevation;
            region->setAttribute(RegionAttributeType::Elevation, data);
        }
    }
    return true;
}
