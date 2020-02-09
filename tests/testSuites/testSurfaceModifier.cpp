
#include <catch.hpp>

#include <GeoPlanetLib/modifiers/RandomColorModifier.h>

using namespace gp;

TEST_CASE("testModifierAF") {
    auto factoryName = SurfaceModifier::list();
    REQUIRE(factoryName.size() > 0);
    auto modifier = SurfaceModifier::create(factoryName[0]);
    REQUIRE(modifier != nullptr);
	REQUIRE(modifier->apply(Surface()));
}
