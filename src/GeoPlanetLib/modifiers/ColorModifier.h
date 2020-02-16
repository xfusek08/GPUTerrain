#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfaceModifier.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT ColorModifier : public SurfaceModifier
        {
        public:
            // properties
            glm::uvec3 color = glm::uvec3(255, 255, 255);

            // methods
            ColorModifier() {}

            virtual bool apply(std::shared_ptr<Surface> surface) override;
        };

        REGISTER_AF_TYPE(ColorModifier, SurfaceModifier);
    }
}
