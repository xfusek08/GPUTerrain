#pragma once

#include <memory>
#include <vector>
#include <TerrainLib/terrainlib_export.h>
#include <glm/glm.hpp>

// TMP:
#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb/stb_image.h>
// END TMP

namespace tl
{
    class PlanetTextureGenerator
    {
    public:
        PlanetTextureGenerator(std::shared_ptr<PlanetSurface> surface);

        TERRAINLIB_EXPORT std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height)
        {
            int width, height, nrChannels;
            unsigned char *data = stbi_load(EARTH_CUBE_MAP_PNG, &width, &height, &nrChannels, 0);

            glm::uvec2 texOffset = glm::uvec2(0, 0);
            switch (faceId) {
                case 0: texOffset = glm::uvec2((width / 4) * 2, height / 3); break;
                case 1: texOffset = glm::uvec2(0, height / 3); break;
                case 2: texOffset = glm::uvec2(width / 4, 0); break;
                case 3: texOffset = glm::uvec2(width / 4, height / 3 * 2); break;
                case 4: texOffset = glm::uvec2(width / 4, height / 3); break;
                case 5: texOffset = glm::uvec2(width / 4 * 3, height / 3); break;
            }

            auto tex = std::make_unique<unsigned char[]>(face_width * face_height * 4);
            for (unsigned int y = 0; y < face_height; ++y) {
                for (unsigned int x = 0; x < face_width;  ++x) {

                    glm::uvec2 coords = glm::uvec2(
                        texOffset.x + x * width / (4.f * face_width),
                        texOffset.y + y * height / (3.f * face_height)
                    );

                    unsigned int i = (4 * x) + (4 * face_width * y);
                    unsigned int j = (nrChannels * coords.x) + (nrChannels * coords.y * width);

                    tex[i + 0] = data[j + 0];
                    tex[i + 1] = data[j + 1];
                    tex[i + 2] = data[j + 2];
                    tex[i + 3] = data[j + 3];
                }
            }

            stbi_image_free(data);
            return tex;
        }
    }

    class PlanetSurface
    {
    public:
        PlanetSurface()
        {
            frontFace   = make_shared<FaceTreeNode>();
            backFace    = make_shared<FaceTreeNode>();
            topFace     = make_shared<FaceTreeNode>();
            bottomFace  = make_shared<FaceTreeNode>();
            leftFace    = make_shared<FaceTreeNode>();
            rightFace   = make_shared<FaceTreeNode>();
        }

        std::shared_ptr<FaceTreeNode> frontFace;
        std::shared_ptr<FaceTreeNode> backFace;
        std::shared_ptr<FaceTreeNode> topFace;
        std::shared_ptr<FaceTreeNode> bottomFace;
        std::shared_ptr<FaceTreeNode> leftFace;
        std::shared_ptr<FaceTreeNode> rightFace;
    };

    class FaceTreeNode
    {
    public:
        const int REGIONS_PER_NODE = 5;

        float topLeftX;
        float topLeftY;
        float bottomRightX;
        float bottomRightY;

        std::vector<FaceRegion> regions;

        std::shared_ptr<FaceTreeNode> neighborFaceTop;
        std::shared_ptr<FaceTreeNode> neighborFaceBottom;
        std::shared_ptr<FaceTreeNode> neighborFaceLeft;
        std::shared_ptr<FaceTreeNode> neighborFaceRight;
    };

    class FaceRegion
    {
    public:
        glm::vec2 position;
    };
}
