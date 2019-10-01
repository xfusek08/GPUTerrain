#pragma once

#include <memory>
#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    class PlanetSurface;

    class PlanetTextureGenerator
    {
    public:
        TERRAINLIB_EXPORT PlanetTextureGenerator(std::shared_ptr<PlanetSurface> surface): _surface(surface) {}

        TERRAINLIB_EXPORT std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height);

    private:
        std::shared_ptr<PlanetSurface> _surface;

        unsigned int computeIndexForImage(unsigned int faceId, unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int chanels);
    };
}
