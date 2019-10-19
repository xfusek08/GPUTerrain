#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <TerrainLib/types.h>
#include <TerrainLib/PlanetCoordinateSystem.h>

#include <TerrainLib/terrainlib_export.h>

namespace tl
{
    class SurfaceRegion
    {
    public:
        // constructor
		TERRAINLIB_EXPORT SurfaceRegion(std::shared_ptr<PlanetCoordinateSystem> coordinateSystem = nullptr, RegionID id = INVALID_REGION_ID);

        // getters
        TERRAINLIB_EXPORT inline bool         isInvalid()             const { return _id == INVALID_REGION_ID; }
        TERRAINLIB_EXPORT inline RegionID     getId()                 const { return _id; }
        TERRAINLIB_EXPORT inline FaceID       getFaceId()             const { return _faceId; }
        TERRAINLIB_EXPORT inline glm::uvec2   getGridCoords()         const { return _gridCoords; }
        TERRAINLIB_EXPORT inline glm::vec2    getLocalPointPosition() const { return _localPointPosition; }
        TERRAINLIB_EXPORT inline glm::uvec4   getColor()              const { return _color; }
        TERRAINLIB_EXPORT inline glm::vec3    get3dPosition()         const { return _3dPos; }

        // setters
        TERRAINLIB_EXPORT inline void setLocalPointPosition(glm::vec2 position) { _localPointPosition = position; _3dPos = _coordinateSystem->localFaceCoordsToGlobal(_faceId, _localPointPosition); }
        TERRAINLIB_EXPORT inline void setColor(glm::uvec4 color)                { _color = color; }

        // methods

        /** Sets local point position to random plane inside its grid. */
        TERRAINLIB_EXPORT void randomizeLocalPoint();

        /** Sets color to random. */
        TERRAINLIB_EXPORT void randomizeColor();

    private:
        RegionID    _id;
        FaceID      _faceId;
        glm::uvec2  _gridCoords;
        glm::vec2   _localPointPosition;
        glm::uvec4  _color;
        glm::vec3   _3dPos;

        std::shared_ptr<PlanetCoordinateSystem> _coordinateSystem;
    };
}
