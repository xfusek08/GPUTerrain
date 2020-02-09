#pragma once

#include <map>

#include <GeoPlanetLib/SurfacePosition.h>
#include <GeoPlanetLib/RegionAttribute.h>
#include <GeoPlanetLib/geoplanetlib_export.h>

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
    };
}
