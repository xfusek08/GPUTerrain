#pragma once

#include <vector>
#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    TERRAINLIB_EXPORT class Mesh
    {
    public:
        std::vector<float>     vertices;
        std::vector<float>     normals;
        std::vector<unsigned>  indicies;
    };
}