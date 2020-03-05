#pragma once

#include <glm/glm.hpp>

#include <GeoPlanetLib/CoordinateTypes.h>

namespace gp
{
    struct LocalPosition {
        FaceID    faceId = FaceID::FACE_INVALID;
        glm::vec2 coords = glm::vec2(0,0);
    };

    class CoordinateSystem
    {
    public:
        // methods
        CoordinateSystem(unsigned int resolution);

        /** Returns resolution of the system. */
        inline unsigned int getResolution() const { return resolution; }

        /** Returns total number of regions on surface. */
		inline unsigned int getTotalRegionCount() const { return resolution * resolution * 6; }

        /** Warps local in face position to compensate for normalization. */
        glm::vec2 warp(glm::vec2 lCoords) const;

        /** Unvarp warped local position to flat cube surface */
        glm::vec2 unwarp(glm::vec2 wlCoords) const;

        /** Return a faceid of region id */
		FaceID faceIdFromRegionId(RegionID RegionID) const;

        /** Converts local face position to global space position on unit sphere. */
        glm::vec3 localToGlobalPos(LocalPosition lPos, bool doWarp = true) const;

        /** Converts global space position on unit sphere to local face position. */
        LocalPosition globalToLocalPos(glm::vec3 gPos) const;

        LocalPosition gridCoordsToLocalPos(FaceID faceId, glm::ivec2 gridCoords) const;

        /**
         * @brief Calculates region id and region inner offset from local face position.
         *
         * @param lPos Local position to be transformed.
         * @param offsetReference vector where region inner offset calculated from face coords will be stored if it's not null
         * @param allowWrap flag allowing wrap operation if coordinates surpasses an edge.
         * @return RegionID Resultign region id possible on a new face.
         */
        RegionID localPosToRegion(LocalPosition lPos, glm::vec2 *offsetReference = nullptr, bool allowWrap = true) const;
        inline RegionID localPosToRegion(FaceID faceId, glm::uvec2 gridCoords, bool allowWrap = true) const
        {
            return localPosToRegion(gridCoordsToLocalPos(faceId, gridCoords), nullptr, allowWrap);
        }

        /**
         * @brief perform and wrap operation on LocalPosition if necessary
         *
         * @param lPos position to be wrapped
         * @return LocalPosition warped position or with invalid face id on not allowed double wrap.
         */
        LocalPosition wrapLocalPosition(LocalPosition lPos) const;

        /** @brief Returns x, y grid coordinates for region id. */
		glm::ivec2 regionIdToGridCoords(RegionID regionId) const;

        /** @brief Returns local face position of topleft corner of region */
		LocalPosition regionIdToLocalPos(RegionID regionId) const;

    private:
        // constants
        const float WARP_MAGIC_ANGLE = 0.868734829276f;

        // properties
        unsigned int resolution;

        // methods

        /** Returns a permutation matrix for face of given faceid. */
        glm::mat3 facePermutationMatrix(FaceID faceId) const;

        /** Returns face id of face which is intersected by direction vector */
        FaceID CoordinateSystem::faceFromGlobalPos(glm::vec3 gPos) const;

        /** Transforms local face coordinates to non-rotated 3d coordinates. (z - is always 1) */
		glm::vec3 makeLocal3D(glm::vec2 pos2D) const;

		/** Transforms non-rotated local 3d coordinates to local 2d coordinates */
		glm::vec2 makeLocal2D(glm::vec3 pos3D) const;
    };
}
