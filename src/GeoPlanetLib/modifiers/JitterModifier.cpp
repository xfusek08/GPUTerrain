#pragma once

#include <GeoPlanetLib/modifiers/JitterModifier.h>

using namespace gp;
using namespace gp::modifiers;

JitterModifier::JitterModifier()
{
}

bool JitterModifier::apply(std::shared_ptr<Surface> surface)
{
	return true;
}
