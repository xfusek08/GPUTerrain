
#include <GeoPlanetLib/TectonicPlate.h>
#include <GeoPlanetLib/Surface.h>
#include <GeoPlanetLib/Utils.h>

using namespace gp;

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

TectonicPlate::TectonicPlate(std::shared_ptr<Surface> surface) :
    elevation(rand_f(-0.5, 0.5)),
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
    return true;
}

bool TectonicPlate::expand()
{
    if (expansionFinished) {
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
    expansionFinished = !regionAdded;
    return regionAdded;
}
