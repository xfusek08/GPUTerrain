#pragma once

#include <GeoPlanetLib/modifiers/JitterModifier.h>
#include <GeoPlanetLib/Utils.h>

using namespace gp;
using namespace gp::modifiers;
using namespace glm;

bool JitterModifier::apply(std::shared_ptr<Surface> surface)
{
    setJitter(getFloatVariable("jitter"));

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

void JitterModifier::setJitter(float value)
{
    if (value < 0) {
        value = 0;
    } else if (value > 1) {
        value = 1;
    }
    jitter = value;
    setFloatVariable("jitter", jitter);
}
