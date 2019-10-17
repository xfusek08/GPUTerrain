
#pragma once

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
}