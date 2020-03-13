#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/Region.h>

namespace gp
{
    class Surface;

    typedef std::vector<std::shared_ptr<TectonicPlate>> PlateList;

    class GEOPLANETLIB_EXPORT TectonicPlate
    {
    public:
        // static methods
        static TectonicPlate *getPlateOfRegion(std::shared_ptr<Region> region);

        /**
         * Assigns a tectonic plate to region as RegionAttribute.
         *
         * @param plate         pointer to tectonic plate to be assigned to region
         * @param region        region which will be given a tectonic plate
         * @param forceOverride flag forcing a override to potential existing plate on region.
         * @return true         if region didn't have a tetonic plate assigned or forceOverride flag was set to true.
         * @return false        if region already had a tectonic plate and forceOverride was set to false.
         */
        static bool assignPlateToRegion(TectonicPlate *plate, std::shared_ptr<Region> region, bool forceOverride = false);

        static void removePlateFromRegion(std::shared_ptr<Region> region);

        static void removePlatesFromSurface(std::shared_ptr<Surface> surface);

        // properties
        float elevation;
        glm::vec3 shiftVector;

        // Methods
        TectonicPlate(std::shared_ptr<Surface> surface);

        inline const RegionList& getMemberRegions()    const { return memberRegions; }
        inline const RegionList& getEdgeRegions()      const { return edgeRegions; }
        inline bool              isExpansionFinished() const { return expansionFinished; }


        /**
         * Assigns given region to this plate if it's not member of another plate
         *
         * @param region
         * @return true if region was successfully assigned
         * @return false if region was refused due to having a region already
         */
        bool addRegion(std::shared_ptr<Region> region);


        bool expand();
        void finishExpansion();
        glm::vec3 getCenter();
        void computeRamdomShift();

    private:
        // Properties
        RegionList memberRegions;
        RegionList edgeRegions;
        std::shared_ptr<Surface> surface;
        glm::vec3 center;
        bool expansionFinished = false;
    };
}
