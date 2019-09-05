#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <TerrainLib/terrainlib_export.h>
#include <TerrainLib/Mesh.h>

namespace tl
{
    class TerrainFace
    {
    public:
        TERRAINLIB_EXPORT TerrainFace(int resolution, glm::vec3 localUp);
        TERRAINLIB_EXPORT std::shared_ptr<Mesh> getMesh() const { return _mesh; }
    protected:
        void buildMesh();

        std::shared_ptr<Mesh> _mesh;
        int                   _resolution;
        glm::vec3             _localUp;
        glm::vec3             _axisA;
        glm::vec3             _axisB;
    };
}