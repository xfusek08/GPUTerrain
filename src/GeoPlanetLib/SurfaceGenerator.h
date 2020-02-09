#pragma once

#include <vector>
#include <memory>

#include <GeoPlanetLib/geoplanetlib_export.h>

#include <GeoPlanetLib/Surface.h>
#include <GeoPlanetLib/SurfaceModifier.h>

#define DEFAULT_MODIFIER_CONFIG { "JitterModifier", "RandomColorModifier" }

namespace gp
{
    struct ModifierListItem
    {
        std::string ident;
        bool enabled;
        std::shared_ptr<SurfaceModifier> modifier;
    };

    typedef std::vector<ModifierListItem> ModifierList;

    class GEOPLANETLIB_EXPORT SurfaceGenerator
    {
    public:
        // methods
		SurfaceGenerator(const std::vector<std::string>& modifierConfig = DEFAULT_MODIFIER_CONFIG);

		const ModifierList& getModifiers() { return modifierList; }

        ModifierListItem getModifier(std::string ident);

        ModifierListItem addModifier(std::string ident, std::shared_ptr<SurfaceModifier> modifier, bool enabled = true);
        ModifierListItem addModifier(std::string ident, std::string modifierClass, bool enabled = true);


        inline ModifierListItem addModifier(std::string ident, const char *modifierClass, bool enabled = true) { return addModifier(ident, std::string(modifierClass), enabled); }
        inline ModifierListItem addModifier(std::string modifierClass, bool enabled = true) { return addModifier(modifierClass, modifierClass, enabled); }

        bool removeModifier(std::string ident);
        bool disableModifier(std::string ident);
        bool enableModifier(std::string ident);

        bool applyModifiers(std::shared_ptr<Surface> surface);

        std::shared_ptr<Surface> generate(unsigned int resolution = 0);

    private:
        // properties
		ModifierList modifierList;

        // methods
        ModifierList::iterator findModifierByIdent(std::string ident);
        ModifierListItem* getModifierReference(std::string ident);
    };
}
