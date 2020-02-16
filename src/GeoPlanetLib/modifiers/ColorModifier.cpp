#pragma once

#include <GeoPlanetLib/modifiers/ColorModifier.h>

using namespace gp;
using namespace gp::modifiers;

bool ColorModifier::apply(std::shared_ptr<Surface> surface)
{
	for (auto region : surface->getRegions()) {
        RegionAttribute attr = RegionAttribute();
        attr.data.uVector3 = color;
        region->attributes[RegionAttributeType::Color] = attr;
    }
	return true;
}
