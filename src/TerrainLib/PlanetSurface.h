#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <TerrainLib/types.h>
#include <TerrainLib/SurfaceConfig.h>
#include <TerrainLib/SurfaceRegion.h>

#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    class PlanetCoordinateSystem;

    class PlanetSurface
    {
    public:
        // constructor
		TERRAINLIB_EXPORT PlanetSurface(SurfaceConfig config);

        // methods
		SurfaceRegion getRegion(RegionID regionId);
		inline SurfaceRegion getRegion(FaceID faceId, glm::ivec2 gridCoords) { return getRegion(_coordinateSystem->getRegionIdByGrid(faceId, gridCoords)); }
		inline SurfaceRegion getRegion(FaceID faceId, int x, int y)          { return getRegion(_coordinateSystem->getRegionIdByGrid(faceId, x ,y)); }
		inline SurfaceRegion getRegion(FaceID faceId, glm::vec2 faceCoords)  { return getRegion(_coordinateSystem->getRegionIdByLocalCoords(faceId, faceCoords)); }
		inline SurfaceRegion getRegion(FaceID faceId, float x, float y)      { return getRegion(_coordinateSystem->getRegionIdByLocalCoords(faceId, x, y)); }
		inline SurfaceRegion getRegion(glm::vec3 position3D)                 { return getRegion(_coordinateSystem->getRegionIdBy3dPosition(position3D)); }
        inline SurfaceRegion getRegion(float x, float y, float z)            { return getRegion(_coordinateSystem->getRegionIdBy3dPosition(x, y, z)); }

        /** Serachs for region with nearest point to given coordinates including wrapping around face edges. */
        SurfaceRegion getNearestRegionByPoint(FaceID faceId, glm::vec2 faceCoords, bool *onEdge);
        inline SurfaceRegion getNearestRegionByPoint(FaceID faceId, float x, float y, bool *onEdge) { return getNearestRegionByPoint(faceId, glm::vec2(x, y), onEdge); }

        /** Returns a vector of surrounding regions */
        std::vector<SurfaceRegion> getRegionNeighbors(SurfaceRegion region);

    private:
        std::unique_ptr<SurfaceRegion[]> _regions;
        std::shared_ptr<PlanetCoordinateSystem> _coordinateSystem;
        SurfaceConfig _config;

        /** Initializes region array. */
        void initRegions();
    };
}
