#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfaceModifier.h>
#include <GeoPlanetLib/Region.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT JitterModifier : public SurfaceModifier
        {
        public:
            // methods
            JitterModifier();

            inline float getJitter() { return jitter; }

            void setJitter(float value);

            bool apply(std::shared_ptr<Surface> surface) override;

            void jitterRegion(std::shared_ptr<Region> region);

        private:
            // properties
            float jitter = 1.0;

            // methods
            float rand_f() const;            ///< Generates random float value from 0.0 to 1.0
            float rand_f(float range) const; ///< Generates random float value from 0.0 to range
        };

        REGISTER_AF_TYPE(JitterModifier, SurfaceModifier);
    }
}
