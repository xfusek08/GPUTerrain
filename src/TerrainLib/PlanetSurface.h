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

        // getters
		TERRAINLIB_EXPORT SurfaceRegion getRegion(RegionID regionId) const;
		TERRAINLIB_EXPORT inline SurfaceRegion getRegion(FaceID faceId, glm::ivec2 gridCoords) const { return getRegion(_coordinateSystem->getRegionIdByGrid(faceId, gridCoords)); }
		TERRAINLIB_EXPORT inline SurfaceRegion getRegion(FaceID faceId, int x, int y)          const { return getRegion(_coordinateSystem->getRegionIdByGrid(faceId, x ,y)); }
		TERRAINLIB_EXPORT inline SurfaceRegion getRegion(FaceID faceId, glm::vec2 faceCoords)  const { return getRegion(_coordinateSystem->getRegionIdByLocalCoords(faceId, faceCoords)); }
		TERRAINLIB_EXPORT inline SurfaceRegion getRegion(FaceID faceId, float x, float y)      const { return getRegion(_coordinateSystem->getRegionIdByLocalCoords(faceId, x, y)); }
		TERRAINLIB_EXPORT inline SurfaceRegion getRegion(glm::vec3 position3D)                 const { return getRegion(_coordinateSystem->getRegionIdBy3dPosition(position3D)); }
        TERRAINLIB_EXPORT inline SurfaceRegion getRegion(float x, float y, float z)            const { return getRegion(_coordinateSystem->getRegionIdBy3dPosition(x, y, z)); }

        /** Const vector reference to region vector for read only acces without copying whole vector. */
        TERRAINLIB_EXPORT const std::vector<SurfaceRegion>& getRegions()                       const { return _regions; }

        // methods

        /** Serachs for region with nearest point to given coordinates including wrapping around face edges. */
        TERRAINLIB_EXPORT SurfaceRegion getNearestRegionByPoint(FaceID faceId, glm::vec2 faceCoords, bool *onEdge);
        TERRAINLIB_EXPORT inline SurfaceRegion getNearestRegionByPoint(FaceID faceId, float x, float y, bool *onEdge) { return getNearestRegionByPoint(faceId, glm::vec2(x, y), onEdge); }

        /** Returns a vector of surrounding regions */
        TERRAINLIB_EXPORT std::vector<SurfaceRegion> getRegionNeighbors(SurfaceRegion region);

    private:
        std::shared_ptr<PlanetCoordinateSystem> _coordinateSystem;
        std::vector<SurfaceRegion> _regions;
        SurfaceConfig _config;

        /** Initializes region array. */
        void initRegions();
    };
}
