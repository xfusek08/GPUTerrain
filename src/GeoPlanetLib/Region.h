#pragma once

#include <map>
#include <vector>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfacePosition.h>
#include <GeoPlanetLib/RegionAttribute.h>

namespace gp
{

    class GEOPLANETLIB_EXPORT Region
    {
    public:
        // propertires
        SurfacePosition position;
        std::map<RegionAttributeType, RegionAttribute> attributes;

        // methods
		Region(SurfacePosition position) : position(position) {}

        inline RegionID getID() const { return position.getRegionID(); }

        inline RegionNeighborhood getNeighborhood() const { return position.getNeighborhood(); }
    };

	typedef std::vector<std::shared_ptr<Region>> RegionList;
}
