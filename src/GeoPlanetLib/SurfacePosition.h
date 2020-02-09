#pragma once

#include <glm/glm.hpp>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/CoordinateSystem.h>

namespace gp
{
    /**
     * @brief A class providing correct geometrical transformations on surface of the cubesphere
     */
    class GEOPLANETLIB_EXPORT SurfacePosition
    {
    public:
        SurfacePosition(CoordinateSystem coordinateSystem, RegionID regionId, glm::vec2 localOffset = glm::vec2(0.5, 0.5))
            : coordinateSystem(coordinateSystem), regionId(regionId), localOffset(localOffset) {}

        SurfacePosition(CoordinateSystem coordinateSystem, FaceID faceId, glm::vec2 localPosition)
            : coordinateSystem(coordinateSystem) { setLocal(faceId, localPosition); }

        SurfacePosition(CoordinateSystem coordinateSystem, glm::vec3 globalPosition)
            : coordinateSystem(coordinateSystem) { setGlobal(globalPosition); }

        glm::vec3 getGlobal()      const; ///< A 3d position on surface of unit sphere.
        glm::vec2 getLocal()       const; ///< A 2d position in current face from top left corner from 0 to 1
        glm::vec2 getLocalOffset() const; ///< A 2d position in current region from top left corner from 0 to 1
        glm::vec2 getLocalWarped() const; ///< A 2d position in current face warped for normalization
        RegionID  getRegionID()    const; ///< Id of current region
        FaceID    getFaceID()      const; ///< id of current face

        /// Sets position from global space
        void setGlobal(glm::vec3);

        /// Sets position from local face position
        void setLocal(FaceID faceId, glm::vec2 position);

        /// Sets position from local face warped position
        void setLocalWarped(FaceID faceId, glm::vec2 warpedPosition);

        /// Sets position from region id and inner region offset
        void setLocalOffset(RegionID region, glm::vec2 position);

    private:
        // properties
        RegionID  regionId    = INVALID_REGION_ID;
        glm::vec2 localOffset = glm::vec2(0.5, 0.5);
        CoordinateSystem coordinateSystem;
    };
}
