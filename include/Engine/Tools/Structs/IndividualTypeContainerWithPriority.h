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
    class IndividualTypeContainerWithPriority
    {
    private:
        struct ContainerElement
        {
            std::type_index type;
            BaseType *element;
            size_t priority;
        };

    public:
        IndividualTypeContainerWithPriority()
            : container()
            , typeToContainerIndex()
        {}
        
        IndividualTypeContainerWithPriority(size_t size)
            : container(size)
            , typeToContainerIndex(size)
        {}

        IndividualTypeContainerWithPriority(const IndividualTypeContainerWithPriority &rhs)
            : container(rhs.container)
            , typeToContainerIndex(rhs.typeToContainerIndex)
        {
            auto it = container.begin();
            auto rhsIt = rhs.container.begin();
            for (; rhsIt != rhs.container.end(); ++it, ++rhsIt)
            {
                BaseType *clonedElement = static_cast<BaseType *>(rhsIt->element->Clone());
                it->element = clonedElement;
            }
        }

        IndividualTypeContainerWithPriority(IndividualTypeContainerWithPriority &&rhs) noexcept
            : container(std::move(rhs.container))
            , typeToContainerIndex(std::move(rhs.typeToContainerIndex))
        {
            rhs.container.clear();
            rhs.typeToContainerIndex.clear();
        }

        IndividualTypeContainerWithPriority &operator=(const IndividualTypeContainerWithPriority &rhs)
        {
            DeleteElements();
            container = rhs.container;
            typeToContainerIndex = rhs.typeToContainerIndex;

            auto it = container.begin();
            auto rhsIt = rhs.container.begin();
            for (; rhsIt != rhs.container.end(); ++it, ++rhsIt)
            {
                BaseType *clonedElement = static_cast<BaseType *>(rhsIt->element->Clone());
                it->element = clonedElement;
            }
            return *this;
        }

        IndividualTypeContainerWithPriority &operator=(IndividualTypeContainerWithPriority &&rhs) noexcept
        {
            DeleteElements();
            container = std::move(rhs.container);
            typeToContainerIndex = std::move(rhs.typeToContainerIndex);
            rhs.container.clear();
            rhs.typeToContainerIndex.clear();
            return *this;
        }

        ~IndividualTypeContainerWithPriority()
        {
            Clear();
        }

    public:
        template<typename Type, typename... Args, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        Type *const Emplace(Args&&... args, size_t priority)
        {
            Type *element = new Type(this, std::forward<Args>(args)...);
            AddInner<Type>(element, priority);
            return element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        Type *const Emplace(size_t priority)
        {
            Type *element = new Type(this);
            AddInner<Type>(element, priority);
            return element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        void Add(Type *element, size_t priority)
        {
            if (!element)
            {
                LOG_ERROR("Element is null");
                return;
            }

            AddInner<Type>(element, priority);
        }

    private:
        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        void AddInner(Type *element, size_t priority)
        {
            std::type_index type = std::type_index(typeid(Type));
            AddInner(type, element, priority);
        }

        void AddInner(const std::type_index &type, BaseType *element, size_t priority)
        {
            if (typeToContainerIndex.contains(type))
            {
                LOG_ERROR("Already contains this type of element");
                return;
            }

            ContainerElement containerElement(type, element, priority);

            auto pos = std::find_if(container.begin(), container.end(),
                [priority](const ContainerElement &containerElement) { return containerElement.priority > priority; }
            );

            size_t index = 0;
            if (pos == container.end())
            {
                container.push_back(std::move(containerElement));
                index = container.size() - 1;
            }
            else
            {
                pos = container.insert(pos, std::move(containerElement));
                index = pos - container.begin();
            }

            typeToContainerIndex.insert(std::make_pair(std::move(type), index));
            UpdateTypeToIndexByScripts(index);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        const ContainerElement &GetContainerElement() const
        {
            size_t index = GetIndex<Type>();
            return container[index];
        }

        const ContainerElement &GetContainerElement(const std::type_index &type) const
        {
            size_t index = GetIndex(type);
            return container[index];
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        size_t const GetIndex() const
        {
            std::type_index type = std::type_index(typeid(Type));
            return GetIndex(type);
        }

        size_t const GetIndex(const std::type_index& type) const
        {
            return typeToContainerIndex.at(type);
        }

    public:
        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        bool Contains() const
        {
            std::type_index type = std::type_index(typeid(Type));
            return Contains(type);
        }

        bool Contains(const std::type_index &type) const
        {
            return typeToContainerIndex.contains(type);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        void Remove()
        {
            std::type_index type = std::type_index(typeid(Type));
            Remove(type);
        }

        void Remove(const std::type_index &type)
        {
            size_t index = typeToContainerIndex[type];
            ContainerElement &containerElement = container[index];

            delete containerElement.element;
            container.erase(container.begin() + index);
            typeToContainerIndex.erase(type);
            UpdateTypeToIndexByScripts(index);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        size_t const GetPriority() const
        {
            const ContainerElement &containerElement = GetContainerElement<Type>();
            return containerElement.priority;
        }

        size_t const GetPriority(const std::type_index &type) const
        {
            const ContainerElement &containerElement = GetContainerElement(type);
            return containerElement.priority;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        size_t const GetCallOrder() const
        {
            return GetIndex<Type>();
        }

        size_t const GetCallOrder(const std::type_index &type) const
        {
            return GetIndex(type);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        Type *const Get() const
        {
            const ContainerElement &containerElement = GetContainerElement<Type>();
            return static_cast<Type *const>(containerElement.element);
        }

        BaseType *const Get(const std::type_index &type) const
        {
            const ContainerElement &containerElement = GetContainerElement(type);
            return containerElement.element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type>>>
        void SetPriority(size_t priority)
        {
            std::type_index type = std::type_index(typeid(Type));
            SetPriority(type, priority);
        }

        void SetPriority(const std::type_index &type, size_t priority)
        {
            size_t index = GetIndex(type);
            ContainerElement &containerElement = container[index];
            containerElement.priority = priority;
            SortScriptsAfterPriorityChangeOfOneElement(index);
        }



    private:
        void UpdateTypeToIndexByScripts(size_t start)
        {
            if (start >= container.size())
            {
                LOG_ERROR("Can't update order after the end of container");
            }

            for (auto it = container.begin() + start; it != container.end(); ++it)
            {
                typeToContainerIndex[it->type] = it - container.begin();
            }
        }

        void SortScriptsAfterPriorityChangeOfOneElement(size_t start)
        {
            if (start >= container.size())
            {
                LOG_ERROR("Can't update order after the end of container");
            }

            auto changedElementIt = container.begin() + start;
            auto nextElementIt = changedElementIt + 1;
            const size_t changedElementPriority = changedElementIt->priority;
            while (nextElementIt != container.end() || changedElementPriority > nextElementIt->priority)
            {
                std::iter_swap(changedElementIt, nextElementIt);
                ++changedElementIt;
                ++nextElementIt;
            }
        }

        void DeleteElements()
        {
            for (auto it = container.begin(); it != container.end(); ++it)
            {
                delete it->element;
            }
        }

    public:
        auto begin() { return container.begin(); }
        auto end() { return container.end(); }
        auto begin() const { return container.begin(); }
        auto end() const { return container.end(); }


        void Clear()
        {
            DeleteElements();
            container.clear();
            typeToContainerIndex.clear();
        }

    private:
        std::vector<ContainerElement> container;
        std::unordered_map<std::type_index, size_t> typeToContainerIndex;
    };
}