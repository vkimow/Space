#pragma once

#include <unordered_map>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <algorithm>
#include "Engine/Tools/Interfaces/IClonable.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Tools::Structs
{
    template<typename BaseType>
    class TypeMapUnordered
    {
    public:
        TypeMapUnordered()
            : typeToElement()
        {}
        
        TypeMapUnordered(size_t size)
            : typeToElement(size)
        {}

        TypeMapUnordered(const TypeMapUnordered &rhs)
            : typeToElement(rhs.typeToElement)
        {
            for (auto it = typeToElement.begin(); it != typeToElement.end(); ++it)
            {
                BaseType *clonedElement = static_cast<BaseType *>(it->second->Clone());
                it->second = clonedElement;
            }
        }

        TypeMapUnordered(TypeMapUnordered &&rhs) noexcept
            : typeToElement(std::move(rhs.typeToElement))
        {
            rhs.typeToElement.clear();
        }

        TypeMapUnordered &operator=(const TypeMapUnordered &rhs)
        {
            DeleteElements();
            typeToElement = rhs.typeToElement;

            for (auto it = typeToElement.begin(); it != typeToElement.end(); ++it)
            {
                BaseType *clonedElement = static_cast<BaseType *>(it->second->Clone());
                it->second = clonedElement;
            }
            return *this;
        }

        TypeMapUnordered &operator=(TypeMapUnordered &&rhs) noexcept
        {
            DeleteElements();
            typeToElement = std::move(rhs.typeToElement);
            rhs.typeToElement.clear();
            return *this;
        }

        ~TypeMapUnordered()
        {
            Clear();
        }

    public:
        template<typename Type, typename... Args, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        Type *const Emplace(Args&&... args)
        {
            Type *element = new Type(std::forward<Args>(args)...);
            AddInner<Type>(element);
            return element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        Type *const Emplace()
        {
            Type *element = new Type();
            AddInner<Type>(element);
            return element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        void Add(Type *element)
        {
            if (!element)
            {
                LOG_ERROR("Element is null");
                return;
            }

            AddInner<Type>(element);
        }

    private:
        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        void AddInner(Type *element)
        {
            std::type_index type = std::type_index(typeid(Type));
            AddInner(type, element);
        }

        void AddInner(const std::type_index &type, BaseType *element)
        {
            if (typeToElement.contains(type))
            {
                LOG_ERROR("Already contains this type of element");
                return;
            }

            typeToElement.emplace(type, element);
        }

    public:
        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        bool Contains() const
        {
            return typeToElement.contains(std::type_index(typeid(Type)));
        }

        bool Contains(const std::type_index &type) const
        {
            return typeToElement.contains(type);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        void Remove()
        {
            std::type_index type = std::type_index(typeid(Type));
            Remove(type);
        }

        void Remove(const std::type_index &type)
        {
            delete typeToElement[type];
            typeToElement.erase(type);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        Type *const Get() const
        {
            return static_cast<Type *const>(typeToElement.at(std::type_index(typeid(Type))));
        }

        BaseType *const Get(const std::type_index &type) const
        {
            return typeToElement.at(type);
        }

    private:
        void DeleteElements()
        {
            for (auto it = typeToElement.begin(); it != typeToElement.end(); ++it)
            {
                delete it->second;
            }
        }

    public:
        auto begin() { return typeToElement.begin(); }
        auto end() { return typeToElement.end(); }
        auto begin() const { return typeToElement.begin(); }
        auto end() const { return typeToElement.end(); }


        void Clear()
        {
            DeleteElements();
            typeToElement.clear();
        }

    private:
        std::unordered_map<std::type_index, BaseType*> typeToElement;
    };
}