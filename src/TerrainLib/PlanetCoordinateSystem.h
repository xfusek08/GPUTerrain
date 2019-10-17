#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <TerrainLib/types.h>

namespace tl
{
	class PlanetCoordinateSystem
	{
	public:

		// constructor
		PlanetCoordinateSystem(unsigned int resolution) : _resolution(resolution) {}

		// getters
		inline unsigned int getResolution() { return _resolution; }

		// methods

		/** Returns total number of regions on surface. */
		unsigned int getTotalRegionCount();

		/** return a faceid of region id */
		FaceID getFaceIdFromRegionId(RegionID RegionID);

		/** Returns faceid of face which vector direction intersects. */
		FaceID getFaceIdFrom3dPosition(glm::vec3 position);

		/** Returns a permutation matrix for face of given faceid. */
		glm::mat3 getPermutationMatrixByFaceId(FaceID faceId);

		/** Returns x, y coordinates in grid int particular face for region id. */
		glm::uvec2 getGridCoordsForId(RegionID RegionID);

		/** Gets coordinates of face grid on which real coord lies. */
		glm::ivec2 localFaceCoordsToGridCoords(float x, float y);
		inline glm::ivec2 localFaceCoordsToGridCoords(glm::vec2 coords) { return localFaceCoordsToGridCoords(coords.x, coords.y); }

		/** Transforms local face coordinates to non-rotated 3d coordinates. (z - is always 1) */
		glm::vec3 local2dTo3d(glm::vec2 local2dCoords);

		/** Transforms ono-rotated local 3d coordinates to local 2d coordinates */
		glm::vec2 local3dTo2d(glm::vec3 local3dCoords);

		glm::vec3 localFaceCoordsToGlobal(FaceID faceId, glm::vec2 localCoords);

        /** Tries to retrive a region id of grid cell with given coords, returns INVALID_REGION_ID if coords are outside of face. */
        RegionID getRegionOnFace(FaceID faceId, int x, int y);
        inline RegionID getRegionOnFace(FaceID faceId, glm::ivec2 gridCoords) { return getRegionOnFace(faceId, gridCoords.x, gridCoords.y); }
        inline RegionID getRegionOnFace(FaceID faceId, float x, float y)      { return getRegionOnFace(faceId, localFaceCoordsToGridCoords(x ,y)); }
        inline RegionID getRegionOnFace(FaceID faceId, glm::vec2 coords)      { return getRegionOnFace(faceId, localFaceCoordsToGridCoords(coords)); }

        /**
         * Returns region on face grid on coordinates x, y.
         * It is possible to surpass the edge of face with coordinates lesser than zero or grater than resolution,
         * then proper wrap is performed and id of region on neighbor face is returned.
         */
        RegionID getRegionIdByGrid(FaceID faceId, glm::ivec2 gridCoords);
        inline RegionID getRegionIdByGrid(FaceID faceId, int x, int y) { return getRegionIdByGrid(faceId, glm::ivec2(x, y) ); }

        /**
         * Returns region on face which grid cell contains local coordinates given by x, y coordinates.
         * It is possible to surpass the edge of face with coordinates lesser than 0 or grater than 1,
         * then proper wrap is performed and id of region on neighbor face is returned.
         */
        RegionID getRegionIdByLocalCoords(FaceID faceId, glm::vec2 localCoords);
        inline RegionID getRegionIdByLocalCoords(FaceID faceId, float x, float y) { return getRegionIdByLocalCoords(faceId, glm::vec2(x, y)); }

        /**
         * Returns region from any face which grid cell is intersected with 3D vector direction.
         */
        RegionID getRegionIdBy3dPosition(glm::vec3 position3D);
        inline RegionID getRegionIdBy3dPosition(float x, float y, float z) { return getRegionIdBy3dPosition(glm::vec3(x, y, z)); }

    private:
        unsigned int _resolution;
    };
}
