
#include <TerrainLib/Terrain.h>

using namespace tl;

Terrain::Terrain() {}

Terrain::~Terrain() {}

void Terrain::generate() {
  _vertices = std::vector<float> {
   -1.0f,  -1.0f,  0.0f,
    1.0f,  -1.0f,  0.0f,
    0.0f,   1.0f,  0.0f,
  };

  _indicies = std::vector<unsigned> {
    0, 1, 2
  };
}
