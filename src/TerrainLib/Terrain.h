#pragma once

#include <vector>
#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    class Terrain
    {
    public:
        TERRAINLIB_EXPORT Terrain();
        TERRAINLIB_EXPORT ~Terrain();
        TERRAINLIB_EXPORT void generate();
        TERRAINLIB_EXPORT std::vector<float>    getVertices() const { return _vertices; }
        TERRAINLIB_EXPORT std::vector<unsigned> getIndicies() const { return _indicies; }
    private:
        std::vector<float>     _vertices;
        std::vector<unsigned>  _indicies;
    };
}
