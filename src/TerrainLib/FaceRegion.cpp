
#include <TerrainLib/FaceRegion.h>

using namespace tl;
using namespace glm;

FaceRegion::FaceRegion(float x, float y) : FaceRegion(vec2(x, y))
{   
}

FaceRegion::FaceRegion(vec2 center) : center(center)
{
    color = uvec4(
        rand() % 256,
        rand() % 256,
        rand() % 256,
        0
    );
}
