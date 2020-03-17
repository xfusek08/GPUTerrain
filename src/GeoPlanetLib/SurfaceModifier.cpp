
#include <GeoPlanetLib/SurfaceModifier.h>

DEFINE_AF_BASE_STORAGE(gp::SurfaceModifier);

using namespace gp;

SurfaceModifier::SurfaceModifier()
{
    initVariables();
}

ModifierVariable SurfaceModifier::getVariable(std::string ident) const
{
    auto it = variables.find(ident);
    if (it == variables.end()) {
        return {};
    }
    return it->second;
}

void SurfaceModifier::setVariable(std::string ident, ModifierVariableData data)
{
    auto it = variables.find(ident);
    if (it != variables.end()) {
        variables[ident].value = data;
    }
}

void SurfaceModifier::addIntegerVariable(std::string name, std::string description, int value)
{
    ModifierVariable var;
    var.type = ModifierVariableType::Integer;
    var.description = description;
    var.value.intVal = value;
    addVariable(name, var);
}

void SurfaceModifier::addBoolVariable(std::string name, std::string description, bool value)
{
    ModifierVariable var;
    var.type = ModifierVariableType::Bool;
    var.description = description;
    var.value.boolval = value;
    addVariable(name, var);
}

void SurfaceModifier::addFloatVariable(std::string name, std::string description, float value)
{
    ModifierVariable var;
    var.type = ModifierVariableType::Float;
    var.description = description;
    var.value.floatVal = value;
    addVariable(name, var);
}

void SurfaceModifier::addVariable(std::string name, ModifierVariable variable)
{
    variables[name] = variable;
}
