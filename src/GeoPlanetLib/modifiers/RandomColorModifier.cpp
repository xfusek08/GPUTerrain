#pragma once

#include <GeoPlanetLib/modifiers/RandomColorModifier.h>

using namespace gp;
using namespace gp::modifiers;

bool RandomColorModifier::apply(std::shared_ptr<Surface> surface)
{
	for (auto region : surface->getRegions()) {

        RegionAttribute attr = RegionAttribute();
        attr.data.uVector3 = glm::uvec3(
            rand() % 255,
            rand() % 255,
            rand() % 255
        );

        region->attributes[RegionAttributeType::Color] = attr;
    }
	return true;
}
