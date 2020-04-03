#pragma once

#include <map>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/modifiers/ModifierFactory.h>

#include <vendor/PerlinNoise/PerlinNoise.hpp>

namespace gp
{
    namespace modifiers
    {
        class GEOPLANETLIB_EXPORT ElevationModifier : public SurfaceModifier
        {
        public:
            // methods
            ElevationModifier(ModifierType type) : SurfaceModifier(type) { initVariables(); }

            virtual bool apply(std::shared_ptr<Surface> surface) override;

        protected:
            // methods
            void initVariables() override
            {
                addFloatVariable("elevationRandomRange", "Range around 0 of random plate elevation", 0.8);
                addBoolVariable("usePlateCollisions", "Use plate collisions", true);
                addBoolVariable("useFilter", "Use smooth filter on terrain", true);
                addBoolVariable("usePerlin", "Use 3d perlin noise", true);
                addFloatVariable("perlinFrequency", "Frequency of perlin noise", 15);
                addFloatVariable("collisionStrength", "Collision strength multiplier", 1);
                addIntegerVariable("perlinOctaves", "Octaves for perlin noise", 1);
                addFloatVariable("perlinStrength", "Multiplier for perlin noise", 0.5);
            }

        private:
            // properties
            float elevationRandomRange = 0;
            float collisionStrength = 0;
            bool useFilter = false;
            bool usePerlin = false;
            bool usePlateCollisions = false;

            float perlinFrequency = 0;
            int perlinOctaves = 0;
            float perlinStrength = 0;
            siv::PerlinNoise perlinGenerator;

            // methods
            float computeElevationCoefficient(TectonicPlate* plate1, TectonicPlate* plate2, Region* region1, Region* region2) const;
            float elevationOf(std::shared_ptr<Region> region) const;
            bool  calculatePlateColisions(std::shared_ptr<Surface> surface) const;
        };
    }
}

REGISTER_MODIFIER_TYPE(ElevationModifier);
