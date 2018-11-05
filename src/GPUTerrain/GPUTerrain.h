#pragma once

#include <vector>
#include <GPUTerrain/Fwd.h>
#include <GPUTerrain/gputerrain_export.h>

class gpuTerrain::GPUTerrain {
  public:
    GPUTERRAIN_EXPORT GPUTerrain();
    GPUTERRAIN_EXPORT ~GPUTerrain();
    GPUTERRAIN_EXPORT void generate();
    GPUTERRAIN_EXPORT std::vector<float> getTriangles()const { return _triangles; }
    GPUTERRAIN_EXPORT std::vector<float> getColors()const    { return _colors; }
    GPUTERRAIN_EXPORT std::vector<int>   getIndeces()const   { return _indeces; }
  private:
    std::vector<float> _triangles;
    std::vector<float> _colors;
    std::vector<int>   _indeces;
};
