#pragma once

#include <vector>
#include <memory>
#include <TerrainLib/terrainlib_export.h>
#include <TerrainLib/TerrainFace.h>

namespace tl
{
    class Terrain
    {
    public:
        TERRAINLIB_EXPORT Terrain(int resolution);
        TERRAINLIB_EXPORT std::vector<std::shared_ptr<TerrainFace>> getFaces() const { return _faces; }
    private:
        std::vector<std::shared_ptr<TerrainFace>> _faces; // 6 faces on cube
    };
}
