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
            // constants
            const unsigned int DEFAULT_NUMBER_OF_PLATES = 50;

            // properties
            unsigned int numberOfPlates = TectonicPlateModifier::DEFAULT_NUMBER_OF_PLATES;
            bool stepMode = false;
            bool expansionFinished = false;

            // methods
            TectonicPlateModifier() : SurfaceModifier() { initVariables(); }

            virtual bool apply(std::shared_ptr<Surface> surface) override;
            bool stepExpandPlates(std::shared_ptr<Surface> surface);

        protected:
            // methods
            void initVariables() override
            {
                addFloatVariable("expansionRateRange", "Range around 0 of random expansion speeds");
            }

        private:
            // properties
            std::map<TectonicPlate*, float> expansionRateMap;

            // methods
            void runPlateFloddFill(std::shared_ptr<Surface> surface);
            bool stepExpandPlate(std::shared_ptr<TectonicPlate> plate);
        };

        REGISTER_AF_TYPE(TectonicPlateModifier, SurfaceModifier);
    }
}
