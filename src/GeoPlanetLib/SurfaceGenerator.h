#pragma once

#include <vector>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/Surface.h>
#include <GeoPlanetLib/modifiers/SurfaceModifier.h>

#define DEFAULT_MODIFIER_CONFIG { "JitterModifier", "RandomColorModifier" }

namespace gp
{
    struct ModifierListItem
    {
        std::string ident;
        bool enabled;
        std::shared_ptr<modifiers::SurfaceModifier> modifier;
    };

    typedef std::vector<ModifierListItem> ModifierList;

    class GEOPLANETLIB_EXPORT SurfaceGenerator
    {
    public:
        // methods
		SurfaceGenerator(const std::vector<std::string>& modifierConfig = DEFAULT_MODIFIER_CONFIG);

		const ModifierList& getModifiers() { return modifierList; }

        ModifierListItem getModifier(std::string ident);

        ModifierListItem addModifier(std::string ident, std::shared_ptr<modifiers::SurfaceModifier> modifier, bool enabled = true);
        ModifierListItem addModifier(std::string ident, modifiers::ModifierType type, bool enabled = true);

        inline ModifierListItem addModifier(modifiers::ModifierType type, bool enabled = true) { return addModifier(type, type, enabled); }

        bool removeModifier(std::string ident);
        bool disableModifier(std::string ident);
        bool enableModifier(std::string ident);

        bool applyModifiers(std::shared_ptr<Surface> surface);
        bool applyModifier(std::shared_ptr<Surface> surface, std::shared_ptr<modifiers::SurfaceModifier> modifier);
        bool applyModifierItem(std::shared_ptr<Surface> surface, ModifierListItem modifierItem);

        inline bool applyModifier(std::shared_ptr<Surface> surface, std::string ident) { return applyModifierItem(surface, getModifier(ident)); }

        std::shared_ptr<Surface> generate(unsigned int resolution = 0);

    private:
        // properties
		ModifierList modifierList;

        // methods
        ModifierList::iterator findModifierByIdent(std::string ident);
        ModifierListItem* getModifierReference(std::string ident);
    };
}
