#pragma once

#include <map>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/SurfaceModifier.h>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT TectonicPlateModifier : public SurfaceModifier
        {
        public:

            // methods
            TectonicPlateModifier() : SurfaceModifier() { initVariables(); }

            inline bool isExpansionFinished() const { return expansionFinished; }

            virtual bool apply(std::shared_ptr<Surface> surface) override;
            bool stepExpansion(std::shared_ptr<Surface> surface);

        protected:
            // methods
            void initVariables() override
            {
                addIntegerVariable("plateNumber", "Number of plates", 50);
                addFloatVariable("expansionRateRange", "Random expansion speed range around 0", 1);
                addBoolVariable("randomDriven", "Allow random driven expansion", false);
                addBoolVariable("stepMode", "Allow step mode", false);
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

        REGISTER_AF_TYPE(TectonicPlateModifier, SurfaceModifier);
    }
}
