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
        };

        REGISTER_AF_TYPE(ElevationModifier, SurfaceModifier);
    }
}
