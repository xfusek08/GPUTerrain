#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <TerrainLib/types.h>
#include <TerrainLib/PlanetCoordinateSystem.h>

namespace tl
{
    class SurfaceRegion
    {
    public:
        // constructor
		SurfaceRegion(std::shared_ptr<PlanetCoordinateSystem> coordinateSystem = nullptr, RegionID id = INVALID_REGION_ID);

        // getters
        inline bool         isInvalid()             { return _id == INVALID_REGION_ID; }
        inline RegionID     getId()                 { return _id; }
        inline FaceID       getFaceId()             { return _faceId; }
        inline glm::uvec2   getGridCoords()         { return _gridCoords; }
        inline glm::vec2    getLocalPointPosition() { return _localPointPosition; }
        inline glm::uvec4   getColor()              { return _color; }
        inline glm::vec3    get3dPosition()         { return _3dPos; }

        // setters
        inline void setLocalPointPosition(glm::vec2 position) { _localPointPosition = position; _3dPos = _coordinateSystem->localFaceCoordsToGlobal(_faceId, _localPointPosition); }
        inline void setColor(glm::uvec4 color)                { _color = color; }

        // methods

        /** Sets local point position to random plane inside its grid. */
        void randomizeLocalPoint();

        /** Sets color to random. */
        void randomizeColor();

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
