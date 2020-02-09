#pragma once

#include <glm/glm.hpp>

#include <GeoPlanetLib/CoordinateTypes.h>

namespace gp
{
    class CoordinateSystem
    {
    public:
        // methods
        CoordinateSystem(unsigned int resolution);

        /** Returns resolution of the system. */
        inline unsigned int getResolution() const { return resolution; }

        /** Returns total number of regions on surface. */
		inline unsigned int getTotalRegionCount() const { return resolution * resolution * 6; }

    private:
        // properties
        unsigned int resolution;
    };
}
