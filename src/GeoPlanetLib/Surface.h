#pragma once

#include <vector>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/CoordinateSystem.h>
#include <GeoPlanetLib/Region.h>
#include <GeoPlanetLib/TectonicPlate.h>

namespace gp
{
    class GEOPLANETLIB_EXPORT Surface
    {
    public:
        // constants
        static const unsigned int DEFAULT_RESOLUTION = 50;
        static const unsigned int MAX_RESOLUTION = 100;

        // Properties
        PlateList plates;

        // methods
        Surface(unsigned int resolution = Surface::DEFAULT_RESOLUTION);
        ~Surface();

        void clear();
        void reset();

        inline unsigned int getResolution()                     const { return coordinateSystem.getResolution(); }
        inline CoordinateSystem getCoordinateSystem()           const { return coordinateSystem; }
		inline std::shared_ptr<Region> getRegion(RegionID id)   const { return regions[id]; }
        inline std::shared_ptr<Region> getRegion(glm::vec3 pos) const { return regions[coordinateSystem.globalPosToRegion(pos)]; }

        const RegionList& getRegions() const { return regions; }

    private:
        // properties
        CoordinateSystem coordinateSystem;
		RegionList regions;

        // methods
        void regionInit();
    };
}
