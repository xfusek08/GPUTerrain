
#include <GeoPlanetLib/modifiers/SurfaceModifier.h>

using namespace gp;
using namespace gp::modifiers;

SurfaceModifier::SurfaceModifier(ModifierType type) : type(type)
{
    initVariables();
}

bool SurfaceModifier::getBool(std::string ident)
{
    auto v = getVariableReference(ident);
    if (v != nullptr) {
        return v->getBool();
    }
}

void SurfaceModifier::setBool(std::string ident, bool value)
{
    auto v = getVariableReference(ident);
    if (v != nullptr) {
        return v->setBool(value);
    }
}

int SurfaceModifier::getInt(std::string ident)
{
    auto v = getVariableReference(ident);
    if (v != nullptr) {
        return v->getInt();
    }
}

void SurfaceModifier::setInt(std::string ident, int value)
{
    auto v = getVariableReference(ident);
    if (v != nullptr) {
        return v->setInt(value);
    }
}

float SurfaceModifier::getFloat(std::string ident)
{
    auto v = getVariableReference(ident);
    if (v != nullptr) {
        return v->getFloat();
    }
}

void SurfaceModifier::setFloat(std::string ident, float value)
{
    auto v = getVariableReference(ident);
    if (v != nullptr) {
        return v->setFloat(value);
    }
}

// protected

void SurfaceModifier::defineVariable(ModifierVariable variable)
{
    variables.emplace(variable.getIdent(), variable);
}

ModifierVariable* SurfaceModifier::getVariableReference(std::string ident)
{
    auto it = variables.find(ident);
    if (it == variables.end()) {
        return nullptr;
    }
    return &it->second;
}
