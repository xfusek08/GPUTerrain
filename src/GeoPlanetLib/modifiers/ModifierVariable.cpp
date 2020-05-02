
#include <GeoPlanetLib/modifiers/ModifierVariable.h>

using namespace std;
using namespace gp::modifiers;

// ============================================================================
// STATIC
// ============================================================================

ModifierVariable::ModifierVariable(string ident, string description, bool default) : type(ModifierVariableType::Bool), ident(ident), description(description)
{
    data.boolVar = { false };
    setBool(default);
}

ModifierVariable::ModifierVariable(string ident, string description, int default, int minVal, int maxVal) : type(ModifierVariableType::Integer), ident(ident), description(description)
{
    data.intVar = { 0, minVal, maxVal };
    setInt(default);
}

ModifierVariable::ModifierVariable(string ident, string description, float default, float minVal, float maxVal) : type(ModifierVariableType::Float), ident(ident), description(description)
{
    data.floatVar = { 0.f, minVal, maxVal };
    setFloat(default);
}

// ============================================================================
// NON STATIC
// ============================================================================

bool ModifierVariable::getBool() const
{
    if (type == ModifierVariableType::Bool) {
        return data.boolVar.value;
    }
    return false;
}

void ModifierVariable::setBool(bool value)
{
    if (type == ModifierVariableType::Bool) {
        data.boolVar.value = value;
    }
}

int ModifierVariable::getInt() const
{
    if (type == ModifierVariableType::Integer) {
        return data.intVar.value;
    }
    return 0;
}

void ModifierVariable::setInt(int value)
{
    if (type == ModifierVariableType::Integer) {
        data.intVar.value = value;
        if (data.intVar.value > data.intVar.max) {
            data.intVar.value = data.intVar.max;
        } else if (data.intVar.value < data.intVar.min) {
            data.intVar.value = data.intVar.min;
        }
    }
}

float ModifierVariable::getFloat() const
{
    if (type == ModifierVariableType::Float) {
        return data.floatVar.value;
    }
    return 0;
}

void ModifierVariable::setFloat(float value)
{
    if (type == ModifierVariableType::Float) {
        data.floatVar.value = value;
        if (data.intVar.value > data.intVar.max) {
            data.intVar.value = data.intVar.max;
        } else if (data.intVar.value < data.intVar.min) {
            data.intVar.value = data.intVar.min;
        }
    }
}
