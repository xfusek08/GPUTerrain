
#include <random>

#include <GeoPlanetLib/modifiers/TectonicPlateModifier.h>

using namespace gp;
using namespace gp::modifiers;
using namespace std;


/**
 * Used
 * https://stackoverflow.com/questions/22883840/c-get-random-number-from-0-to-max-long-long-integer
 * post about large random number generators
 */
bool TectonicPlateModifier::apply(std::shared_ptr<Surface> surface)
{
    colorMap.clear();
    surface->plates.clear();
    TectonicPlate::removePlatesFromSurface(surface);

    auto regions = surface->getRegions();

    std::random_device rd;
    std::mt19937_64 eng(rd()); // 64-bit Mersenne Twister 19937 generator
    std::uniform_int_distribution<unsigned long> distr;

    for (unsigned int i = 0; i < numberOfPlates; ++i) {
        auto tectonicPlate = make_shared<TectonicPlate>(surface);
        auto randomIndex = distr(eng) % regions.size();
        tectonicPlate->addRegion(regions[randomIndex]);
        colorMap[tectonicPlate.get()] = glm::uvec3(
            rand() % 255,
            rand() % 255,
            rand() % 255
        );
        surface->plates.push_back(tectonicPlate);
    }

    if (!stepMode) {
        runPlateFloddFill(surface);
    }

    return true;
}

void TectonicPlateModifier::runPlateFloddFill(std::shared_ptr<Surface> surface)
{
    while (!expansionFinished) {
        expansionFinished = stepExpandPlates(surface);
    }
}

bool TectonicPlateModifier::stepExpandPlates(std::shared_ptr<Surface> surface)
{
    if (!expansionFinished) {
        expansionFinished = true;
        for (auto plate : surface->plates) {
            if (plate->expand()) {
                expansionFinished = false;
            }
        }
    }
	return expansionFinished;
}

void TectonicPlateModifier::applyStateAsRegionColors(std::shared_ptr<Surface> surface)
{
    for (auto plate : surface->plates) {
        for (auto region : plate->getMemberRegions()) {
            region->attributes[RegionAttributeType::Color].data.uVector3 = glm::mix(colorMap[plate.get()], glm::uvec3(255,255,255), 0.5);
        }
        for (auto region : plate->getEdgeRegions()) {
            region->attributes[RegionAttributeType::Color].data.uVector3 = colorMap[plate.get()];
        }
    }
}
