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
                defineVariable(ModifierVariable("elevationRandomRange", "Range around 0 of random plate elevation", 0.8f, 0.f, 1.f));
                defineVariable(ModifierVariable("collisionStrength", "Collision strength multiplier", 0.5f, 0.f, 10.f));
                defineVariable(ModifierVariable("perlinFrequency", "Frequency of perlin noise", 15.f, 0.1f, 100.f));
                defineVariable(ModifierVariable("perlinOctaves", "Octaves for perlin noise", 1, 1, 10));
                defineVariable(ModifierVariable("perlinStrength", "Multiplier for perlin noise", 0.2f, 0.f, 10.f));
                defineVariable(ModifierVariable("usePlateCollisions", "Use plate collisions", true));
                defineVariable(ModifierVariable("usePerlin", "Use 3d perlin noise", true));
                defineVariable(ModifierVariable("useFilter", "Use smooth filter on terrain", true));
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
            float computePressure(TectonicPlate* plate1, TectonicPlate* plate2, Region* region1, Region* region2) const;
            float elevationOf(std::shared_ptr<Region> region) const;
            bool  calculatePlateColisions(std::shared_ptr<Surface> surface) const;
        };
    }
}

REGISTER_MODIFIER_TYPE(ElevationModifier);
