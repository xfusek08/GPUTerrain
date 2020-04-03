#pragma once

#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/modifiers/ModifierFactory.h>
#include <GeoPlanetLib/Region.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT JitterModifier : public SurfaceModifier
        {
        public:
            // methods
            JitterModifier(ModifierType type) : SurfaceModifier(type) { initVariables(); }

            bool apply(std::shared_ptr<Surface> surface) override;

        private:
            // properties
            float jitter = 0;

            // methods
            void initVariables() override
            {
                addFloatVariable("jitter", "Jitter of regions", 1.f);
            }

            void jitterRegion(std::shared_ptr<Region> region);
            void setJitter(float value);
        };
    }
}

REGISTER_MODIFIER_TYPE(JitterModifier);
