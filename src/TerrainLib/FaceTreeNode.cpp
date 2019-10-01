
#include <TerrainLib/FaceTreeNode.h>
#include <TerrainLib/FaceRegion.h>

using namespace std;
using namespace tl;
using namespace glm;

float rand_f()
{
    return float(rand()) / float(RAND_MAX);
}

FaceTreeNode::FaceTreeNode(float topLeftX, float topLeftY, float bottomRightX, float bottomRightY) :
	topLeftX(topLeftX),
	topLeftY(topLeftY),
	bottomRightX(bottomRightX),
	bottomRightY(bottomRightY)
{
	// regions.push_back(make_shared<FaceRegion>(bottomRightX / 4, bottomRightX / 4));
	// regions.push_back(make_shared<FaceRegion>(3 * bottomRightX / 4, bottomRightX / 4));
	// regions.push_back(make_shared<FaceRegion>(bottomRightX / 4, 3 * bottomRightX / 4));
	// regions.push_back(make_shared<FaceRegion>(3 * bottomRightX / 4, 3 * bottomRightX / 4));

    for (unsigned int y = 0; y < 5; ++y) {
		for (unsigned int x = 0; x < 5;  ++x) {
            float u = ((rand_f() - 0.5) / 10) + float(x) / 5.0;
            float v = ((rand_f() - 0.5) / 10) + float(y) / 5.0;
            regions.push_back(make_shared<FaceRegion>(u, v));
        }
    }
}

shared_ptr<FaceRegion> FaceTreeNode::getRegionOnCoords(float x, float y)
{
	return getRegionOnCoords(vec2(x, y));
}

shared_ptr<FaceRegion> FaceTreeNode::getRegionOnCoords(vec2 coords)
{
    if (!hasCoords(coords)) {
        return nullptr;
    }

    // todo walk through subfaces ...

    shared_ptr<FaceRegion> closestRegion = regions[0];
    float closestDistace = distance(closestRegion->center, coords);

    for (int i = 1; i < regions.size(); ++i) {
        float dist = distance(regions[i]->center, coords);
        if (dist < closestDistace) {
            closestDistace = dist;
            closestRegion = regions[i];
        }
    }
    return closestRegion;
}

bool FaceTreeNode::hasCoords(float x, float y)
{
	return hasCoords(vec2(x, y));
}

bool FaceTreeNode::hasCoords(vec2 coords)
{
    return
		coords.x <= bottomRightX && coords.x >= topLeftX &&
		coords.y <= bottomRightY && coords.y >= topLeftY;
}
