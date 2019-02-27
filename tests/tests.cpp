
#include <iostream>
#include <GPUTerrain.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace gpuTerrain;

TEST_CASE("Terrain constructor test") {
  auto terrain = std::make_unique<GPUTerrain>();
  REQUIRE(terrain != nullptr);
}

TEST_CASE("Terrain generate test") {
  auto terrain = std::make_unique<GPUTerrain>();
  terrain->generate();
  REQUIRE(terrain->getVertices().size() > 0);
  REQUIRE(terrain->getColors().size() == terrain->getVertices().size());
  REQUIRE(terrain->getIndicies().size() == terrain->getVertices().size() / 3);
}
