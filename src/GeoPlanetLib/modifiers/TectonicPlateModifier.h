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
            TectonicPlateModifier() {}

            virtual bool apply(std::shared_ptr<Surface> surface) override;
            bool stepExpandPlates(std::shared_ptr<Surface> surface);
            bool expandStep(std::shared_ptr<Surface> surface);
            void applyStateAsRegionColors(std::shared_ptr<Surface> surface);

        private:
            // properties
            std::map<gp::TectonicPlate *, glm::uvec3> colorMap;

            // methods
            void runPlateFloddFill(std::shared_ptr<Surface> surface);
        };

        REGISTER_AF_TYPE(TectonicPlateModifier, SurfaceModifier);
    }
}
