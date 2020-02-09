#pragma once

#include <glm/glm.hpp>

#include <GeoPlanetLib/geoplanetlib_export.h>

namespace gp
{
    // types
    enum class RegionAttributeType {
        TectonicPlate,
        Elevation,
        Color
    };

    typedef union {
        float scalar;
        glm::vec3 vector3;
    } RegionAttributeData;

    /**
     * @Todo: maybe make an abstract factory ...
     */
    class GEOPLANETLIB_EXPORT RegionAttribute
    {
    public:
        // propertires
         RegionAttributeData data;

        // methods
		RegionAttribute() {}
    };
}
