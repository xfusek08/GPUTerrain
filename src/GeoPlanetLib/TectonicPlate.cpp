
#include <GeoPlanetLib/TectonicPlate.h>
#include <GeoPlanetLib/Surface.h>
#include <GeoPlanetLib/Utils.h>

using namespace gp;

// ============================================================================
// STATIC
// ============================================================================

TectonicPlate *TectonicPlate::getPlateOfRegion(std::shared_ptr<Region> region)
{
	auto attr = region->getAttribute(RegionAttributeType::TectonicPlate);
    if (attr.isValid) {
		return attr.data.plate;
    }
    return nullptr;
}

bool TectonicPlate::assignPlateToRegion(TectonicPlate *plate, std::shared_ptr<Region> region, bool forceOverride)
{
    TectonicPlate *existingPlate;
    if (!forceOverride) {
		existingPlate = TectonicPlate::getPlateOfRegion(region);
    }

    if (forceOverride || existingPlate == nullptr) {
        RegionAttributeData data;
        data.plate = plate;
        region->setAttribute(RegionAttributeType::TectonicPlate, data);
        return true;
    }
    return false;
}

void TectonicPlate::removePlateFromRegion(std::shared_ptr<Region> region)
{
    region->unsetAttribute(RegionAttributeType::TectonicPlate);
}

void TectonicPlate::removePlatesFromSurface(std::shared_ptr<Surface> surface)
{
    for (auto region : surface->getRegions()) {
        TectonicPlate::removePlateFromRegion(region);
    }
}

// ============================================================================
// NON STATIC
// ============================================================================

TectonicPlate::TectonicPlate(std::shared_ptr<Surface> surface) :
    elevation(rand_f(-0.5, 0.5)),
    center(glm::vec3(0)),
    shiftVector(glm::vec3(0)),
    surface(surface)
{
}

bool TectonicPlate::addRegion(std::shared_ptr<Region> region)
{
    if (!TectonicPlate::assignPlateToRegion(this, region)) {
        return false;
    }

    memberRegions.push_back(region);
    edgeRegions.push_back(region);
    center = glm::vec3(0);
    return true;
}

bool TectonicPlate::expand()
{
    if (isExpansionFinished()) {
        return false;
    }

    bool regionAdded = false;
	auto size = edgeRegions.size();
	size_t actIndex = 0;
	for (size_t i = 0; i < size; ++i) {
        bool isOnEdge = false;
        auto region = edgeRegions[actIndex];
        for (auto neighborId : region->getNeighborhood().each()) {
			if (neighborId != INVALID_REGION_ID) {
				auto neighbor = surface->getRegion(neighborId);
				if (addRegion(neighbor)) {
					regionAdded = true;
				}
				else {
					if (TectonicPlate::getPlateOfRegion(neighbor) != this) {
						isOnEdge = true;
					}
				}
			}
        }

        if (!isOnEdge) {
            edgeRegions.erase(edgeRegions.begin() + actIndex);
		} else {
			++actIndex;
		}
    }

    if (!regionAdded) {
        finishExpansion();
    }

    return regionAdded;
}

void TectonicPlate::finishExpansion()
{
    expansionFinished = true;
    computeRamdomShift();
}

glm::vec3 TectonicPlate::getCenter()
{
    if (center == glm::vec3(0) && edgeRegions.size() > 0) {
        for (auto region : edgeRegions) {
            center += region->position.getGlobal();
        }
        center = glm::normalize(center);
    }
    return center;
}

void TectonicPlate::computeRamdomShift()
{
    auto center = getCenter();
    if (center == glm::vec3(0)) {
        shiftVector = glm::vec3(0);
        return;
    }
    auto xAxis = glm::cross(center, glm::vec3(1,0,0));
    auto yAxis = glm::cross(center, glm::vec3(0,1,0));
    auto magnitude = rand_f(0.5, 1);
    shiftVector = glm::normalize(rand_f(-1,1) * xAxis + rand_f(-1,1) * yAxis) * magnitude;
}
