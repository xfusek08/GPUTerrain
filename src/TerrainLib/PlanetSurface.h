#pragma once

#include <memory>
#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    class PlanetSurface
    {
    public:
        TERRAINLIB_EXPORT PlanetSurface();
        TERRAINLIB_EXPORT ~PlanetSurface();
        TERRAINLIB_EXPORT std::unique_ptr<unsigned char[]> getTextureDataForFace(unsigned int faceId, unsigned int face_width, unsigned int face_height);

    private:
        unsigned int computeIndexForImage(unsigned int faceId, unsigned int x, unsigned int y, unsigned int h, unsigned int w, unsigned int chanels);
    };
}
