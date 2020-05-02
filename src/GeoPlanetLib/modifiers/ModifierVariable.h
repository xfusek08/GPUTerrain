#pragma once

#include <string>

#include <GeoPlanetLib/geoplanetlib_export.h>

namespace gp
{
    namespace modifiers
    {
        enum class ModifierVariableType
        {
            Bool, Integer, Float
        };

        typedef struct {
            bool value;
        } BoolVariable;

        typedef struct {
            int value;
            int min;
            int max;
        } IntVariable;

        typedef struct {
            float value;
            float min;
            float max;
        } FloatVariable;

        class GEOPLANETLIB_EXPORT ModifierVariable
        {
        public:
            // properties

            // constructors
            ModifierVariable(std::string ident, std::string description, bool default = false);
            ModifierVariable(std::string ident, std::string description, int default = 0, int minVal = INT_MIN, int maxVal = INT_MAX);
            ModifierVariable(std::string ident, std::string description, float default = 0.0, float minVal = -INFINITY, float maxVal = INFINITY);

            // methods
            inline ModifierVariableType getType()        const { return type; }
            inline std::string          getIdent()       const { return ident; }
            inline std::string          getDescription() const { return description; }

            bool getBool() const;
            void setBool(bool value);

            int getInt() const;
            void setInt(int value);

            float getFloat() const;
            void setFloat(float value);

        protected:
            ModifierVariableType type;
            std::string ident;
            std::string description;

            union {
                BoolVariable  boolVar;
                IntVariable   intVar;
                FloatVariable floatVar;
            } data;
        };
    } // namespace modifiers

} // namespace gp
