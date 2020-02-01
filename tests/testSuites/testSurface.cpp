
#include <catch.hpp>

#include <GeoPlanetLib/Surface.h>

TEST_CASE("SurfaceInitiation") {
    gp::Surface surface = gp::Surface(2);
    REQUIRE(surface.getRegions().size() == 2 * 2 * 6);
}
