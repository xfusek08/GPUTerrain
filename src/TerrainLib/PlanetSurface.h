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

    class TERRAINLIB_EXPORT PlanetSurface
    {
    public:
        // constructor
		PlanetSurface(SurfaceConfig config);

        // getters
		SurfaceRegion getRegion(RegionID regionId) const;
		inline SurfaceRegion getRegion(FaceID faceId, glm::ivec2 gridCoords) const { return getRegion(_coordinateSystem->getRegionIdByGrid(faceId, gridCoords)); }
		inline SurfaceRegion getRegion(FaceID faceId, int x, int y)          const { return getRegion(_coordinateSystem->getRegionIdByGrid(faceId, x ,y)); }
		inline SurfaceRegion getRegion(FaceID faceId, glm::vec2 faceCoords)  const { return getRegion(_coordinateSystem->getRegionIdByLocalCoords(faceId, faceCoords)); }
		inline SurfaceRegion getRegion(FaceID faceId, float x, float y)      const { return getRegion(_coordinateSystem->getRegionIdByLocalCoords(faceId, x, y)); }
		inline SurfaceRegion getRegion(glm::vec3 position3D)                 const { return getRegion(_coordinateSystem->getRegionIdBy3dPosition(position3D)); }
        inline SurfaceRegion getRegion(float x, float y, float z)            const { return getRegion(_coordinateSystem->getRegionIdBy3dPosition(x, y, z)); }

        /**
         * Regions of surface
         *
         * @return const std::vector<SurfaceRegion>& read only vector of all region on the surface
         */
        const std::vector<SurfaceRegion>& getRegions() const { return _regions; }

        // methods
		void setConfig(SurfaceConfig config);

        /** Serachs for region with nearest point to given coordinates including wrapping around face edges. */
        SurfaceRegion getNearestRegionByPoint(FaceID faceId, glm::vec2 faceCoords, bool *onEdge);
        inline SurfaceRegion getNearestRegionByPoint(FaceID faceId, float x, float y, bool *onEdge) { return getNearestRegionByPoint(faceId, glm::vec2(x, y), onEdge); }

        /** Returns a vector of surrounding regions */
        std::vector<SurfaceRegion> getRegionNeighbors(SurfaceRegion region);

    private:
        std::shared_ptr<PlanetCoordinateSystem> _coordinateSystem;
        std::vector<SurfaceRegion> _regions;
        SurfaceConfig _config;

        /** Initializes region array. */
        void initRegions();

		glm::uvec4 getFaceColorForRegion(SurfaceRegion region);
    };
}
