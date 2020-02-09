#pragma once

#include <vector>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/CoordinateSystem.h>

#include <GeoPlanetLib/Region.h>

namespace gp
{
    /** Vector of region pointers */
    typedef std::vector<std::shared_ptr<Region>> RegionList;

    class GEOPLANETLIB_EXPORT Surface
    {
    public:
        // constants
        static const unsigned int DEFAULT_RESOLUTION = 10;

        // methods
        Surface(unsigned int resolution = Surface::DEFAULT_RESOLUTION);

        inline unsigned int getResolution() const { return coordinateSystem.getResolution(); }
		const RegionList&   getRegions()    const { return regions; }

    private:
        // properties
        CoordinateSystem coordinateSystem;
		RegionList regions;
    };
}
