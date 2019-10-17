
#include <TerrainLib/PlanetTextureGenerator.h>
#include <TerrainLib/PlanetSurface.h>
#include <TerrainLib/SurfaceRegion.h>

#include <geGL/Generated/OpenGLConstants.h>

#include <iostream>

#include <glm/glm.hpp>

using namespace std;
using namespace tl;
using namespace glm;

unique_ptr<unsigned char[]> PlanetTextureGenerator::getTextureDataForFace(FaceID faceId, unsigned int width, unsigned int height)
{
	auto tex = make_unique<unsigned char[]>(width * height * 4);
    for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width;  ++x) {
            uvec4 color = uvec4(0,0,0,1);;
			bool onEdge = false;

            // uv coords from 0 to 1
            float u = float(x) / float(width);
            float v = float(y) / float(height);
			auto region = _surface->getNearestRegionByPoint(faceId, u, v, &onEdge);

            if (!onEdge) {
                color = region.getColor();
            }

			unsigned int i = (4 * x) + (4 * width * y);
            tex[i + 0] = color.x;
			tex[i + 1] = color.y;
			tex[i + 2] = color.z;
			tex[i + 3] = color.w;
        }
    }
	return tex;
}

FaceID PlanetTextureGenerator::glCubemapFaceToFaceId(GLuint glCubemapFace)
{
    switch (glCubemapFace)
    {
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X: return FACE_RIGHT;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X: return FACE_LEFT;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y: return FACE_NORTH;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y: return FACE_SOUTH;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z: return FACE_FRONT;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z: return FACE_BACK;
        default: return FACE_INVALID;
    }
}