#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfaceModifier.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT FaceColorModifier : public SurfaceModifier
        {
        // properties
        public:
            float jitter = 1.0;

        // methods
        public:
            FaceColorModifier();

            virtual bool apply(std::shared_ptr<Surface> surface) override;
        };

        REGISTER_AF_TYPE(FaceColorModifier, SurfaceModifier);
    }
}
