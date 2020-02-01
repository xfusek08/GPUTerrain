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
    public: // propertires
    private: // propertires
		RegionList regions;
        std::unique_ptr<CoordinateSystem> coordinateSystem;

    public: // methods
		Surface(unsigned int resolution);

		const RegionList& getRegions() const { return regions; }

    private: // methods
    };
}
