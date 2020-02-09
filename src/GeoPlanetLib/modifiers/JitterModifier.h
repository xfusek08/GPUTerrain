#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfaceModifier.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT JitterModifier : public SurfaceModifier
        {
        // properties
        public:
            float jitter = 1.0;

        // methods
        public:
            JitterModifier();

            virtual bool apply(Surface surface) override;
        };

        REGISTER_AF_TYPE(JitterModifier, SurfaceModifier);
    }
}
