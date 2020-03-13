
#include <random>
#include <unordered_map>

#include <GeoPlanetLib/modifiers/ElevationModifier.h>

using namespace gp;
using namespace gp::modifiers;
using namespace std;

bool ElevationModifier::apply(shared_ptr<Surface> surface)
{
    if (!calculatePlateColisions(surface)) {
        for (auto region : surface->getRegions()) {
            auto plate = TectonicPlate::getPlateOfRegion(region);
            if (plate != nullptr) {
                RegionAttributeData data;
                data.scalar = plate->elevation;
                region->setAttribute(RegionAttributeType::Elevation, data);
            }
        }
    }
    return true;
}

bool ElevationModifier::calculatePlateColisions(shared_ptr<Surface> surface) const
{
    float step =  1 / float(surface->getResolution());
    for (auto plate: surface->plates) {
        for (auto region: plate->getEdgeRegions()) {

            float totalElevation = plate->elevation;

            for (auto neighborID: region->getNeighborhood().each()) {
                if (neighborID == INVALID_REGION_ID) {
                    continue;
                }
                // each existing neighbor region which lays on non processed different palte plate

                // all regions has to have plate
                auto neighbor = surface->getRegion(neighborID);
                auto neighborPlate = TectonicPlate::getPlateOfRegion(neighbor);
                if (neighborPlate == nullptr) {
                    return false;
                }

                if (neighborPlate != plate.get()) {
                    float elevationCoefficient = computeElevationCoefficient(plate.get(), neighborPlate, region.get(), neighbor.get());

                    totalElevation += elevationCoefficient; // for now just sum of all neighbor later maybe average or average weight by magnitude of shift
                }
            }

            RegionAttributeData data;
            data.scalar = totalElevation;
            region->setAttribute(RegionAttributeType::Elevation, data);
        }
    }

    // collisions were successfully computed
    for (auto region : surface->getRegions()) {
        float elevation = elevationOf(region);
        if (elevation == NAN) {
            return false;
        }

        RegionAttributeData data;

        for (auto neighborID: region->getNeighborhood().each()) {
            if (neighborID == INVALID_REGION_ID) {
                continue;
            }
            auto neighbor = surface->getRegion(neighborID);

            auto increment = elevationOf(neighbor);
            if (increment == NAN) {
                return false;
            }

            elevation += increment;
            elevation *= 0.5;
            // data.scalar = elevation * 0.1;
            // neighbor->setAttribute(RegionAttributeType::Elevation, data);
        }

        data.scalar = elevation;
        region->setAttribute(RegionAttributeType::Elevation, data);
    }

    return true;
}

float ElevationModifier::computeElevationCoefficient(TectonicPlate* plate1, TectonicPlate* plate2, Region* region1, Region* region2) const
{
    auto v1 = region1->position.getGlobal();
    auto v2 = region2->position.getGlobal();

    auto direction = glm::normalize(v2 - v1);
    auto t1 = glm::normalize(v1 + plate1->shiftVector) - v1;
    auto t2 = glm::normalize(v2 + plate2->shiftVector) - v2;

    auto d1 = glm::dot(t1, direction) * glm::length(plate1->shiftVector);
    auto d2 = glm::dot(t2, -direction) * glm::length(plate2->shiftVector);

    return d1 + d2;
}

float ElevationModifier::elevationOf(shared_ptr<Region> region) const
{
    auto attr = region->getAttribute(RegionAttributeType::Elevation);
    if (attr.isValid) {
        return attr.data.scalar;
    }

    auto plate = TectonicPlate::getPlateOfRegion(region);
    if (plate == nullptr) {
        return NAN;
    }

    return plate->elevation;
}