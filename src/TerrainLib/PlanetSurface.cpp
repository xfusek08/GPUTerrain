
#include <TerrainLib/PlanetSurface.h>
#include <TerrainLib/FaceTreeNode.h>

using namespace std;
using namespace tl;

PlanetSurface::PlanetSurface()
{
    frontFace   = make_shared<FaceTreeNode>();
    backFace    = make_shared<FaceTreeNode>();
    topFace     = make_shared<FaceTreeNode>();
    bottomFace  = make_shared<FaceTreeNode>();
    leftFace    = make_shared<FaceTreeNode>();
    rightFace   = make_shared<FaceTreeNode>();
}
