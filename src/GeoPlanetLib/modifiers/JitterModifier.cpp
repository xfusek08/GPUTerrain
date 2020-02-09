#pragma once

#include <GeoPlanetLib/modifiers/JitterModifier.h>

using namespace gp;
using namespace gp::modifiers;

JitterModifier::JitterModifier()
{
}

bool JitterModifier::apply(Surface surface)
{
	return true;
}
