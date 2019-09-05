
#include <TerrainLib/TerrainFace.h>

using namespace std;
using namespace tl;

TerrainFace::TerrainFace(int resolution, glm::vec3 localUp) : _resolution(resolution), _localUp(localUp)
{
    _axisA = glm::vec3(_localUp.y, _localUp.z, _localUp.x);
    _axisB = glm::cross(_localUp, _axisA);
    buildMesh();
}

void TerrainFace::buildMesh()
{
    _mesh = make_shared<Mesh>();

    for (int y = 0; y < _resolution; y++) {
        for (int x = 0; x < _resolution; x++) {
            glm::vec2 percent = glm::vec2(x, y) / float(_resolution - 1);
            glm::vec3 vertexOnCube =
                _localUp +
                (percent.x - 0.5f) * 2 * _axisA +
                (percent.y - 0.5f) * 2 * _axisB; 
            
            vertexOnCube = glm::normalize(vertexOnCube);

            _mesh->vertices.push_back(vertexOnCube.x);
            _mesh->vertices.push_back(vertexOnCube.y);
            _mesh->vertices.push_back(vertexOnCube.z);

            if (x != _resolution - 1 && y != _resolution - 1) {
                int i = x + y * _resolution;

                _mesh->indicies.push_back(i);
                _mesh->indicies.push_back(i + _resolution + 1);
                _mesh->indicies.push_back(i + _resolution);

                _mesh->indicies.push_back(i);
                _mesh->indicies.push_back(i + 1);
                _mesh->indicies.push_back(i + _resolution  + 1);
            }
        }
    }
}

