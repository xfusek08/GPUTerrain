#pragma once

#include <map>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/CoordinateTypes.h>
#include <GeoPlanetLib/RegionAttribute.h>

namespace gp
{
    class Region
    {
    public: // propertires
    private: // propertires
		RegionID id = INVALID_REGION_ID;
        std::map<RegionAttributeType, RegionAttribute> attributes;

    public: // methods
		Region(RegionID id) { this->id = id; }

    private: // methods
    };
}
