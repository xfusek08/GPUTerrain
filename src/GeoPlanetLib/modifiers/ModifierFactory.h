#pragma once

#include <memory>
#include <map>

#include <GeoPlanetLib/modifiers/SurfaceModifier.h>

#define REGISTER_MODIFIER_TYPE(modifier_class)\
namespace gp {\
    namespace modifiers {\
        namespace types {\
            const ModifierType modifier_class = #modifier_class;\
        }\
        class modifier_class##Factory : public ModifierFactorySpecific\
        {\
        public:\
            modifier_class##Factory()\
            {\
                ModifierFactory::registerType(types::modifier_class, this);\
            }\
            virtual std::shared_ptr<SurfaceModifier> create(const ModifierType& type) override\
            {\
                return std::make_shared<modifier_class>(type);\
            }\
        };\
        static modifier_class##Factory global_##modifier_class##Factory;\
    }\
}

namespace gp
{
    namespace modifiers
    {
        class ModifierFactorySpecific
        {
        public:
            virtual std::shared_ptr<SurfaceModifier> create(const ModifierType& type) = 0;
        };

        class ModifierFactory
        {
        public:
            // static methods
            static std::shared_ptr<SurfaceModifier> create(const ModifierType& type)
            {
                if (getMap().find(type) == getMap().end()) {
                    return nullptr;
                }

                return getMap()[type]->create(type);
            }

            static std::map<ModifierType, ModifierFactorySpecific*>& getMap()
            {
                static std::map<ModifierType, ModifierFactorySpecific*> map;
                return map;
            }

            static void registerType(const ModifierType& type, ModifierFactorySpecific* factory)
            {
                getMap()[type] = factory;
            }

            static std::vector<ModifierType> list()
            {
                std::vector<ModifierType> result;
                result.reserve(getMap().size());
                for(auto item : getMap()) {
                    result.push_back(item.first);
                }
                return result;
            }
        };
    } // namespace modifiers
} // namespace gp
