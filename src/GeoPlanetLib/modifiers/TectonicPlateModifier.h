#pragma once

#include <map>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/modifiers/ModifierFactory.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT TectonicPlateModifier : public SurfaceModifier
        {
        public:
            // methods
            TectonicPlateModifier(ModifierType type) : SurfaceModifier(type) { initVariables(); }

            inline bool isExpansionFinished() const { return expansionFinished; }

            virtual bool apply(std::shared_ptr<Surface> surface) override;
            bool stepExpansion(std::shared_ptr<Surface> surface);

        protected:
            // methods
            void initVariables() override
            {
                defineVariable(ModifierVariable("plateNumber", "Number of plates", 50, 1, 500));
                defineVariable(ModifierVariable("expansionRateRange", "Random expansion speed range around 0", 0.5f, 0.f, 5.0f));
                defineVariable(ModifierVariable("randomDriven", "Allow random driven expansion", false));
                defineVariable(ModifierVariable("stepMode", "Allow step mode", false));
            }

        private:
            // properties
            bool expansionFinished = false;
            std::map<TectonicPlate*, float> expansionRateMap;

            // methods
            void runPlateFloddFill(std::shared_ptr<Surface> surface);
            void stepExpansionInternal(std::shared_ptr<Surface> surface, bool randomDriven);
            bool stepExpandPlate(std::shared_ptr<TectonicPlate> plate);
        };
    }
}

REGISTER_MODIFIER_TYPE(TectonicPlateModifier);
