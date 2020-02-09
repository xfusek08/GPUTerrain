#pragma once

#include <GeoPlanetLib/modifiers/FaceColorModifier.h>

using namespace gp;
using namespace gp::modifiers;

FaceColorModifier::FaceColorModifier()
{
}

bool FaceColorModifier::apply(Surface surface)
{
	return true;
}
