#pragma once

#include <glm/glm.hpp>

#include <GeoPlanetLib/CoordinateTypes.h>

namespace gp
{
    /** Local position on cube */
    struct LocalPosition {
        FaceID    faceId = FaceID::FACE_INVALID; /// id of face
        glm::vec2 coords = glm::vec2(0,0); /// coordinates in the face
    };

    /**
     * Coordinate system of a surface
     *
     * This class encapsulation all necessary computation for transforming local region position to global position
     */
    class CoordinateSystem
    {
    public:

        // methods

        /** Construct a new Coordinate System object for given surface resolution */
        CoordinateSystem(unsigned int resolution);

        /** Returns resolution of the system. */
        inline unsigned int getResolution() const { return resolution; }

        /** Returns total number of regions on surface. */
		inline unsigned int getTotalRegionCount() const { return resolution * resolution * 6; }

        /** Warps local in face position to compensate for normalization. */
        glm::vec2 warp(glm::vec2 lCoords) const;

        /** Unvarp warped local position to flat cube surface */
        glm::vec2 unwarp(glm::vec2 wlCoords) const;

        /** Computes face id from region id */
		FaceID faceIdFromRegionId(RegionID RegionID) const;

        /**
         * Converts local face position to global space position on unit sphere.
         *
         * @param lPos   Local position which will be converted
         * @param doWarp Flag enabling wrap function to compensate normalization
         *
         * @return glm::vec3 final global position in 3d space.
         */
        glm::vec3 localToGlobalPos(LocalPosition lPos, bool doWarp = true) const;

        /**
         * Projects 3d global space position to local position on uint cube.
         *
         * @param gPos Position in 3d
         * @return LocalPosition Coresponding local postition on unit cube after projection
         */
        LocalPosition globalToLocalPos(glm::vec3 gPos) const;

        /**
         * Converts grid coordinates in local face space to LocalPosition structure.
         *
         * Does not perform a wrap function.
         *
         * @param faceId     If id face which local space is worked on
         * @param gridCoords Integer 2d index to grid ion the face, computed position is corresponding to center of the grid cell.
         *
         * @return LocalPosition Local space position, may not lie on the cube face if grid coords passed beyond edge.
         */
        LocalPosition gridCoordsToLocalPos(FaceID faceId, glm::ivec2 gridCoords) const;

        /**
         * Calculates region id and region inner offset from local face position.
         *
         * @param lPos Local position to be transformed.
         * @param offsetReference vector where region inner offset calculated from face coords will be stored if it's not null
         * @param allowWrap flag allowing wrap operation if coordinates surpasses an edge.
         * @return RegionID Resultign region id possible on a new face.
         */
        RegionID localPosToRegion(LocalPosition lPos, glm::vec2 *offsetReference = nullptr, bool allowWrap = true) const;

        /**
         * Calculates region id and region inner offset from local face grid position.
         *
         * @param faceId     If id face which local space is worked on.
         * @param gridCoords Integer 2d index into grid cell of the face.
         * @param allowWrap  Flag allowing wrap operation if coordinates surpasses an edge.
         * @return RegionID  Resultign region id possible on a new face.
         */
        inline RegionID localPosToRegion(FaceID faceId, glm::uvec2 gridCoords, bool allowWrap = true) const
        {
            return localPosToRegion(gridCoordsToLocalPos(faceId, gridCoords), nullptr, allowWrap);
        }

        /**
         * Calculates region id and region inner offset from global position
         *
         * @param gPos global 3d position
         * @param offsetReference vector where region inner offset calculated from face coords will be stored if it's not null
         * @return RegionID Resultign region id
         */
        inline RegionID globalPosToRegion(glm::vec3 gPos, glm::vec2 *offsetReference = nullptr) const
        {
            if (gPos == glm::vec3(0)) {
                return INVALID_REGION_ID;
            }
            return localPosToRegion(globalToLocalPos(gPos), offsetReference, true);
        }

        /**
         * Performs and wrap operation on LocalPosition if it is necessary
         *
         * @param lPos position to be wrapped
         * @return LocalPosition warped position or LocalPosition with invalid face id if not allowed double wrap was performed.
         */
        LocalPosition wrapLocalPosition(LocalPosition lPos) const;

        /** Returns x, y grid coordinates for region id. */
		glm::ivec2 regionIdToGridCoords(RegionID regionId) const;

        /** Returns local face position of topleft corner of region */
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
