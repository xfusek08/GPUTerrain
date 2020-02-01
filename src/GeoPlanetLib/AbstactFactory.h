#pragma once

#include <memory>
#include <string>
#include <map>
#include <vector>

/**
 * @file Abstract factory tempalte for effortless new types definition.
 * Inspired by: https://blog.noctua-software.com/object-factory-c++.html
 */

template<class T>
class AbstractFactorySpecific
{
public:
    virtual std::shared_ptr<T> create() = 0;
};

template<class T>
class AbstractFactoryBase
{
    private:
        static std::map<std::string, AbstractFactorySpecific<T>*> factoriesMap;

    public:
		static std::shared_ptr<T> create(const std::string& name)
        {
            return factoriesMap[name]->create();
        }

		static void registerType(const std::string& name, AbstractFactorySpecific<T>* factory)
        {
            factoriesMap[name] = factory;
        }

		static std::vector<std::string> list()
        {
            std::vector<std::string> result;
            result.reserve(factoriesMap.size());
            for(auto const& item: factoriesMap) {
                result.push_back(item.first);
            }
            return result;
        }
};

#define DEFINE_AF_BASE_STORAGE(type) std::map<std::string, AbstractFactorySpecific<type>*> type::factoriesMap;

#define REGISTER_AF_TYPE(t_specific,t_base)\
	class t_specific##Factory : public AbstractFactorySpecific<t_base>\
	{\
		public:\
			t_specific##Factory()\
			{\
				t_base::registerType(#t_specific, this);\
			}\
			virtual std::shared_ptr<t_base> create() override\
			{\
				return std::make_shared<t_specific>();\
			}\
	};\
	static t_specific##Factory global_##t_specific##Factory
