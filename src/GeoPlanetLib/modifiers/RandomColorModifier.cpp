#pragma once

#include <GeoPlanetLib/modifiers/RandomColorModifier.h>

using namespace gp;
using namespace gp::modifiers;

RandomColorModifier::RandomColorModifier()
{
}

bool RandomColorModifier::apply(std::shared_ptr<Surface> surface)
{
	return true;
}
