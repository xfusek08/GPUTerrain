
#include <TerrainLib/PlanetSurface.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb/stb_image.h>

using namespace std;
using namespace tl;
using namespace glm;

PlanetSurface::PlanetSurface() {}
PlanetSurface::~PlanetSurface() {}

unique_ptr<unsigned char[]> PlanetSurface::getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height)
{
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

    auto tex = make_unique<unsigned char[]>(face_width * face_height * 4);
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
