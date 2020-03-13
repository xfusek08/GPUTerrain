#pragma once

#include <map>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfaceModifier.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT ElevationModifier : public SurfaceModifier
        {
        public:
            // methods
            ElevationModifier() {}

            virtual bool apply(std::shared_ptr<Surface> surface) override;

        private:

            // methods
            float computeElevationCoefficient(TectonicPlate* plate1, TectonicPlate* plate2, Region* region1, Region* region2) const;
            float elevationOf(std::shared_ptr<Region> region) const;
            bool  calculatePlateColisions(std::shared_ptr<Surface> surface) const;
        };

        REGISTER_AF_TYPE(ElevationModifier, SurfaceModifier);
    }
}
