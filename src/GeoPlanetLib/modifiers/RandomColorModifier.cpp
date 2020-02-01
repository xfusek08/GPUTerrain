#pragma once

#include <GeoPlanetLib/modifiers/RandomColorModifier.h>

using namespace gp;
using namespace gp::modifiers;

RandomColorModifier::RandomColorModifier()
{
}

bool RandomColorModifier::apply(Surface surface)
{
	return true;
}
