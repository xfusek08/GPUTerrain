#pragma once

#include <array>

#include <glm/glm.hpp>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/CoordinateSystem.h>

namespace gp
{
    struct RegionNeighborhood
    {
        static const unsigned int SIZE = 8;

        RegionID
            up        = INVALID_REGION_ID,
            upLeft    = INVALID_REGION_ID,
            left      = INVALID_REGION_ID,
            downLeft  = INVALID_REGION_ID,
            down      = INVALID_REGION_ID,
            downRight = INVALID_REGION_ID,
            right     = INVALID_REGION_ID,
            upRight   = INVALID_REGION_ID;

        std::array<RegionID, RegionNeighborhood::SIZE> each() const
        {
            return { up, upLeft, left, downLeft, down, downRight, right, upRight };
        }
    };

    /**
     * @brief A class providing correct geometrical transformations on surface of the cubesphere
     */
    class GEOPLANETLIB_EXPORT SurfacePosition
    {
    public:
        SurfacePosition(CoordinateSystem coordinateSystem, RegionID regionId, glm::vec2 localOffset = glm::vec2(0.5, 0.5))
            : coordinateSystem(coordinateSystem), regionId(regionId), localOffset(localOffset) {}

        SurfacePosition(CoordinateSystem coordinateSystem, FaceID faceId, glm::vec2 localCoords)
            : coordinateSystem(coordinateSystem) { setLocal(localCoords, faceId); }

        SurfacePosition(CoordinateSystem coordinateSystem, glm::vec3 globalPosition)
            : coordinateSystem(coordinateSystem) { setGlobal(globalPosition); }

        /// Id of current region
        inline RegionID  getRegionID() const { return regionId; }

        /// A 2d position in current region from top left corner from 0 to 1
        inline glm::vec2 getLocalOffset() const { return localOffset; }

        // Coordinate system of attached surface
        inline CoordinateSystem getCoordinateSystem() const { return coordinateSystem; }

        // calculated getters

        FaceID     getFaceID()           const; ///< id of current face
        glm::vec3  getGlobal()           const; ///< A 3d position on surface of unit sphere.
        glm::vec2  getLocal()            const; ///< A 2d position in current face from top left corner from 0 to 1
        glm::vec2  getLocalWarped()      const; ///< A 2d position in current face warped for normalization
        glm::uvec2 getFaceGridPosition() const; ///< A 2d integer index in face grid.

        RegionNeighborhood getNeighborhood() const;

        //setters

        /// Sets position from global space
        void setGlobal(glm::vec3 gPos);
        inline void setGlobal(float gPosX, float gPosY, float gPosZ) { setGlobal(glm::vec3(gPosX, gPosY, gPosZ)); }

        /// Sets position from local position in a face
        void setLocal(glm::vec2 lCoords, FaceID faceId);
        inline void setLocal(glm::vec2 lCoords)                           { setLocal(lCoords, getFaceID()); }
        inline void setLocal(float lCoordX, float lCoordY, FaceID faceId) { setLocal(glm::vec2(lCoordX, lCoordY), faceId); }
        inline void setLocal(float lCoordX, float lCoordY)                { setLocal(glm::vec2(lCoordX, lCoordY), getFaceID()); }

        /// Sets position from local face warped position
        void setLocalWarped(glm::vec2 wlCoords, FaceID faceId);
        inline void setLocalWarped(glm::vec2 wlCoords)                            { setLocalWarped(wlCoords, getFaceID()); }
        inline void setLocalWarped(float wlCoordX, float wlCoordY, FaceID faceId) { setLocalWarped(glm::vec2(wlCoordX, wlCoordY), faceId); }
        inline void setLocalWarped(float wlCoordX, float wlCoordY)                { setLocalWarped(glm::vec2(wlCoordX, wlCoordY), getFaceID()); }

        /// Sets position from region id and inner region offset
        inline void setLocalOffset(glm::vec2 offset)                                { localOffset = glm::clamp(offset, 0.0f, 1.0f); }
        inline void setLocalOffset(glm::vec2 offset, RegionID regionId)             { setLocalOffset(offset); regionId = regionId; }
        inline void setLocalOffset(float offsetX, float offsetY)                    { setLocalOffset(glm::vec2(offsetX, offsetY)); }
        inline void setLocalOffset(float offsetX, float offsetY, RegionID regionId) { setLocalOffset(glm::vec2(offsetX, offsetY), regionId); }

    private:
        // properties
        RegionID  regionId    = INVALID_REGION_ID;
        glm::vec2 localOffset = glm::vec2(0.5, 0.5);
        CoordinateSystem coordinateSystem;
    };
}
