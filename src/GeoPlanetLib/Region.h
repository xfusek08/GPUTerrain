#pragma once

#include <map>
#include <vector>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfacePosition.h>

namespace gp
{
    class TectonicPlate;
}

namespace gp
{
    enum class RegionAttributeType {
        TectonicPlate,
        Elevation,
        Color
    };

    typedef union {
        float scalar;
        TectonicPlate *plate;
    } RegionAttributeData;

    struct RegionAttribute
    {
        RegionAttributeData data;
        bool isValid;
    };

    class GEOPLANETLIB_EXPORT Region
    {
    public:
        // propertires
        SurfacePosition position;

        // methods
		Region(SurfacePosition position) : position(position) {}

        inline RegionID getID() const { return position.getRegionID(); }

        inline RegionNeighborhood getNeighborhood() const { return position.getNeighborhood(); }

        RegionAttribute getAttribute(RegionAttributeType type);

        void setAttribute(RegionAttributeType type, RegionAttributeData data);

        void unsetAttribute(RegionAttributeType type);

    private:
        // propertires
        std::map<RegionAttributeType, RegionAttributeData> attributes;
    };

	typedef std::vector<std::shared_ptr<Region>> RegionList;
}
