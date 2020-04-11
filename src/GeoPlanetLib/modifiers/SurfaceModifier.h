#pragma once

#include <memory>

#include <map>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/Surface.h>

#include <GeoPlanetLib/modifiers/ModifierType.h>

namespace gp
{
    namespace modifiers {
        enum class ModifierVariableType
        {
            Bool, Integer, Float
        };

        typedef union {
            bool boolval;
            int intVal;
            float floatVal;
        } ModifierVariableData;

        struct ModifierVariable
        {
            ModifierVariableType type;
            std::string description;
            ModifierVariableData value;
        };

        class GEOPLANETLIB_EXPORT SurfaceModifier
        {
        public:

            //methods
            SurfaceModifier(ModifierType type);

            virtual bool apply(std::shared_ptr<Surface> surface) = 0;

            inline const std::map<std::string, ModifierVariable>& getVariables() { return variables; }
            inline ModifierType getType() const { return type; }
            inline int getIntegerVariable(std::string ident) const { return getVariable(ident).value.intVal; }
            inline bool getBoolVariable(std::string ident)   const { return getVariable(ident).value.boolval; }
            inline float getFloatVariable(std::string ident) const { return getVariable(ident).value.floatVal; }
            ModifierVariable getVariable(std::string ident)  const;

            inline void setIntegerVariable(std::string ident, int val) { ModifierVariableData data; data.intVal = val; return setVariable(ident, data); }
            inline void setBoolVariable(std::string ident, bool val)   { ModifierVariableData data; data.boolval = val; return setVariable(ident, data); }
            inline void setFloatVariable(std::string ident, float val) { ModifierVariableData data; data.floatVal = val; return setVariable(ident, data); }                        
            void setVariable(std::string ident, ModifierVariableData data);

        protected:
            // properties
            ModifierType type = types::UndefinedModifier;
            std::map<std::string, ModifierVariable> variables;

            // methods
            void addIntegerVariable(std::string ident, std::string description, int value = 0);
            void addBoolVariable(std::string ident, std::string description, bool value = false);
            void addFloatVariable(std::string ident, std::string description, float value = 0.0);
            void addVariable(std::string ident, ModifierVariable variable);

            virtual void initVariables() {};
        };
    }
}
