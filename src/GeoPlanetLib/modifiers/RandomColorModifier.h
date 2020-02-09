#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfaceModifier.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT RandomColorModifier : public SurfaceModifier
        {
        public:
            RandomColorModifier();

            virtual bool apply(std::shared_ptr<Surface> surface) override;
        };

        REGISTER_AF_TYPE(RandomColorModifier, SurfaceModifier);
    }
}
