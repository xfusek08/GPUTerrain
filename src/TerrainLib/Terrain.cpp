
#include <TerrainLib/Terrain.h>
#include <glm/glm.hpp>

using namespace std;
using namespace tl;

Terrain::Terrain(int resolution)
{
    _faces.push_back(make_shared<TerrainFace>(resolution, glm::vec3 {  1, 0, 0 }));
    _faces.push_back(make_shared<TerrainFace>(resolution, glm::vec3 {  0, 1, 0 }));
    _faces.push_back(make_shared<TerrainFace>(resolution, glm::vec3 {  0, 0, 1 }));
    _faces.push_back(make_shared<TerrainFace>(resolution, glm::vec3 { -1, 0, 0 }));
    _faces.push_back(make_shared<TerrainFace>(resolution, glm::vec3 {  0,-1, 0 }));
    _faces.push_back(make_shared<TerrainFace>(resolution, glm::vec3 {  0, 0,-1 }));
}
