#pragma once

#include <memory>
#include <TerrainLib/terrainlib_export.h>
#include <glm/glm.hpp>

namespace tl
{
    class FaceRegion
    {
    public:
        FaceRegion(glm::vec2 center);
        FaceRegion(float x = 0, float y = 0);

        glm::vec2 center;
        glm::uvec4 color;
    };
}
