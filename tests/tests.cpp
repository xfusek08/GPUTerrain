#include<GPUTerrain/GPUTerrain.h>
#include<iostream>

#define CATCH_CONFIG_MAIN
#include<catch.hpp>

using namespace gpuTerrain;

SCENARIO("GetTerrain test") {
  auto terrain = std::make_unique<GPUTerrain>();
  REQUIRE(terrain != nullptr);
  // REQUIRE(terrain->getTrue() == true);
}
