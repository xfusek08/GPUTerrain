#pragma once

#include <GeoPlanetLib/modifiers/JitterModifier.h>
#include <GeoPlanetLib/Utils.h>

using namespace gp;
using namespace gp::modifiers;
using namespace glm;

bool JitterModifier::apply(std::shared_ptr<Surface> surface)
{
    jitter = getFloat("jitter");
	for (auto region : surface->getRegions()) {
        jitterRegion(region);
    }
	return true;
}

void JitterModifier::jitterRegion(std::shared_ptr<Region> region)
{
	float jitterX = (rand_f(jitter) - jitter / 2.0f);
	float jitterY = (rand_f(jitter) - jitter / 2.0f);

    region->position.setLocalOffset(vec2(
        0.5 + jitterX,
        0.5 + jitterY
    ));
}
