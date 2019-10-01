
#include <TerrainLib/PlanetTextureGenerator.h>
#include <TerrainLib/PlanetSurface.h>
#include <TerrainLib/FaceTreeNode.h>
#include <TerrainLib/FaceRegion.h>

#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb/stb_image.h>

using namespace std;
using namespace tl;
using namespace glm;

unique_ptr<unsigned char[]> PlanetTextureGenerator::getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height)
{
	auto tex = make_unique<unsigned char[]>(face_width * face_height * 4);
    shared_ptr<FaceTreeNode> faceNode;
	switch (faceId) {
	 	case 0: faceNode = _surface->frontFace; break;
	 	case 1: faceNode = _surface->backFace; break;
	 	case 2: faceNode = _surface->topFace; break;
	 	case 3: faceNode = _surface->bottomFace; break;
	 	case 4: faceNode = _surface->leftFace; break;
	 	case 5: faceNode = _surface->rightFace; break;
	}

    for (unsigned int y = 0; y < face_height; ++y) {
		for (unsigned int x = 0; x < face_width;  ++x) {
            float u = float(x) / float(face_width);
            float v = float(y) / float(face_height);
			auto region = faceNode->getRegionOnCoords(u, v);

            uvec4 color = region->color;
            auto dist = distance(region->center, vec2(u, v));

            if (distance(region->center, vec2(u, v)) < 0.01) {
                color = uvec4(0,0,0,0);
            }

            // color.x = int(dist * 255.0);
            // color.y = int(dist * 255.0);
            // color.z = int(dist * 255.0);
			// color.w = 1;

            // color.x = int(region->center.x * 255.0);
            // color.y = int(region->center.y * 255.0);
            // color.z = int(region->center.y * 255.0);

			unsigned int i = (4 * x) + (4 * face_width * y);
            tex[i + 0] = color.x;
			tex[i + 1] = color.y;
			tex[i + 2] = color.z;
			tex[i + 3] = color.w;
        }
    }
	return tex;


    int width, height, nrChannels;
    unsigned char *data = stbi_load(EARTH_CUBE_MAP_PNG, &width, &height, &nrChannels, 0);

	uvec2 texOffset = uvec2(0, 0);
	switch (faceId) {
	 	case 0: texOffset = uvec2((width / 4) * 2, height / 3); break;
	 	case 1: texOffset = uvec2(0, height / 3); break;
	 	case 2: texOffset = uvec2(width / 4, 0); break;
	 	case 3: texOffset = uvec2(width / 4, height / 3 * 2); break;
		case 4: texOffset = uvec2(width / 4, height / 3); break;
		case 5: texOffset = uvec2(width / 4 * 3, height / 3); break;
	}

    for (unsigned int y = 0; y < face_height; ++y) {
		for (unsigned int x = 0; x < face_width;  ++x) {

			uvec2 coords = uvec2(
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
