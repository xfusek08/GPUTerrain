#pragma once

#include <memory>

#include <map>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/Surface.h>

#include <GeoPlanetLib/modifiers/ModifierType.h>

#include <GeoPlanetLib/modifiers/ModifierVariable.h>

namespace gp
{
    namespace modifiers {

        class GEOPLANETLIB_EXPORT SurfaceModifier
        {
        public:
            //methods
            SurfaceModifier(ModifierType type);

            virtual bool apply(std::shared_ptr<Surface> surface) = 0;

            inline ModifierType getType() { return type; }

            bool getBool(std::string ident);
            void setBool(std::string ident, bool value);

            int getInt(std::string ident);
            void setInt(std::string ident, int value);

            float getFloat(std::string ident);
            void setFloat(std::string ident, float value);

            inline const std::map<std::string, ModifierVariable>& getVariables() { return variables; }

        protected:
            // properties
            ModifierType type = types::UndefinedModifier;
            std::map<std::string, ModifierVariable> variables;

            // methods
            void defineVariable(ModifierVariable variable);
            ModifierVariable* getVariableReference(std::string ident);

            virtual void initVariables() {};
        };
    }
}
