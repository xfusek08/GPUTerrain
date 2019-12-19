#pragma once

#include <glm/glm.hpp>

namespace tl
{
    typedef unsigned int RegionID;
    const RegionID INVALID_REGION_ID = -1;

    enum FaceID {
        FACE_FRONT = 0,
        FACE_RIGHT,
        FACE_BACK,
        FACE_LEFT,
        FACE_NORTH,
        FACE_SOUTH,
        FACE_INVALID = 99
    };

    struct LocalPlanetCoords
    {
        FaceID faceId = FACE_INVALID;
        glm::vec2 coords = {0, 0};
    };

    class PlanetCoordinates
    {
    public:
        glm::vec3         asOpenGL();
        glm::vec3         asKartesian();
        glm::vec3         asSpherical();
        LocalPlanetCoords asLocal();

        RegionID getRegionId();
    private:
        glm::vec3 openGlCoords = {0, 0, 0};
};
}
