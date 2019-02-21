#include <GPUTerrain.h>

using namespace gpuTerrain;

GPUTerrain::GPUTerrain() {}

GPUTerrain::~GPUTerrain() {}

void GPUTerrain::generate() {
  _vertices = std::vector<float> {
    -1.0f,  -1.0f,   0.0f,
     1.0f,  -1.0f,   0.0f,
     0.0f,   1.0f,   0.0f,
  };

  _colors = std::vector<float> {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
  };

  _indeces = std::vector<int> {
    0, 1, 2
  };
}
