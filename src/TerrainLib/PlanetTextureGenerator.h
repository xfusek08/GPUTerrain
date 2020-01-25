#pragma once

#include <memory>
#include <geGL/Generated/OpenGLTypes.h>

#include <TerrainLib/types.h>

#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    class PlanetSurface;

    class PlanetTextureGenerator
    {
    public:
		TERRAINLIB_EXPORT PlanetTextureGenerator(std::shared_ptr<PlanetSurface> surface): _surface(surface) {}
		TERRAINLIB_EXPORT std::unique_ptr<unsigned char[]> getTextureDataForFace(FaceID faceId, unsigned int face_width, unsigned int face_height);
		TERRAINLIB_EXPORT FaceID glCubemapFaceToFaceId(GLuint glCubemapFace);

	private:
        std::shared_ptr<PlanetSurface> _surface;
    };
}
