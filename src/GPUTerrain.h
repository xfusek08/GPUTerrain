#pragma once

#include <vector>
#include <Fwd.h>
#include <GPUTerrain/gputerrain_export.h>

class gpuTerrain::GPUTerrain
{
  public:
    GPUTERRAIN_EXPORT GPUTerrain();
    GPUTERRAIN_EXPORT ~GPUTerrain();
    GPUTERRAIN_EXPORT void generate();
    GPUTERRAIN_EXPORT std::vector<float> getVertices() const { return _vertices; }
    GPUTERRAIN_EXPORT std::vector<float> getColors()   const { return _colors;   }
    GPUTERRAIN_EXPORT std::vector<int>   getIndicies() const { return _indicies; }
  private:
    std::vector<float> _vertices;
    std::vector<float> _colors;
    std::vector<int>   _indicies;
};
