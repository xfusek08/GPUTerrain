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
        std::map<RegionAttributeType, RegionAttribute> attributes;

        // methods
		Region(SurfacePosition position) : position(position) {}

        inline RegionID        getId()       const { return position.getRegionID(); }
        inline SurfacePosition getPosition() const { return position; }

    private:
        SurfacePosition position;
    };
}
