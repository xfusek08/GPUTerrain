#pragma once

#include <vector>
#include <Fwd.h>

class gpuTerrain::GPUTerrain {
  public:
    GPUTerrain();
    ~GPUTerrain();
    void generate();
    std::vector<float> getVertices() const { return _vertices; }
    std::vector<float> getColors()    const { return _colors;    }
    std::vector<int>   getIndeces()   const { return _indeces;   }
  private:
    std::vector<float> _vertices;
    std::vector<float> _colors;
    std::vector<int>   _indeces;
};
