#pragma once

#include <memory>
#include <vector>
#include <TerrainLib/terrainlib_export.h>
#include <glm/glm.hpp>

namespace tl
{
    class FaceRegion;

    class FaceTreeNode
    {
    public:
        const int REGIONS_PER_NODE = 5;

		FaceTreeNode(float topLeftX = 0, float topLeftY = 0, float  bottomRightX = 1, float bottomRightY = 1);

		std::shared_ptr<FaceRegion> getRegionOnCoords(float x, float y);
		std::shared_ptr<FaceRegion> getRegionOnCoords(glm::vec2 coords);

		bool hasCoords(float x, float y);
		bool hasCoords(glm::vec2 coords);

        float topLeftX;
        float topLeftY;
        float bottomRightX;
        float bottomRightY;

        std::vector<std::shared_ptr<FaceRegion>> regions;
        // std::vector<std::shared_ptr<FaceTreeNode>> subFaces;

        std::shared_ptr<FaceTreeNode> neighborFaceTop    = nullptr;
        std::shared_ptr<FaceTreeNode> neighborFaceBottom = nullptr;
        std::shared_ptr<FaceTreeNode> neighborFaceLeft   = nullptr;
        std::shared_ptr<FaceTreeNode> neighborFaceRight  = nullptr;
    };
}
