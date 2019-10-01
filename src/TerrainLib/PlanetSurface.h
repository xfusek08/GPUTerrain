#pragma once

#include <memory>
#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    class FaceTreeNode;

    class PlanetSurface
    {
    public:
        TERRAINLIB_EXPORT PlanetSurface();

        std::shared_ptr<FaceTreeNode> frontFace;
        std::shared_ptr<FaceTreeNode> backFace;
        std::shared_ptr<FaceTreeNode> topFace;
        std::shared_ptr<FaceTreeNode> bottomFace;
        std::shared_ptr<FaceTreeNode> leftFace;
        std::shared_ptr<FaceTreeNode> rightFace;
    };
}
