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
    class TypeMapWithPriority
    {
    private:
        struct ContainerElement
        {
            std::type_index type;
            BaseType *element;
            size_t priority;
        };

    public:
        TypeMapWithPriority()
            : container()
            , typeToContainerIndex()
        {}

        TypeMapWithPriority(size_t size)
            : container(size)
            , typeToContainerIndex(size)
        {}

        TypeMapWithPriority(const TypeMapWithPriority &rhs)
            : container(rhs.container)
            , typeToContainerIndex(rhs.typeToContainerIndex)
        {
            for (auto it = container.begin(); it != container.end(); ++it)
            {
                BaseType *clonedElement = static_cast<BaseType *>(it->element->Clone());
                it->element = clonedElement;
            }
        }

        TypeMapWithPriority(TypeMapWithPriority &&rhs) noexcept
            : container(std::move(rhs.container))
            , typeToContainerIndex(std::move(rhs.typeToContainerIndex))
        {
            rhs.container.clear();
            rhs.typeToContainerIndex.clear();
        }

        TypeMapWithPriority &operator=(const TypeMapWithPriority &rhs)
        {
            DeleteElements();
            container = rhs.container;
            typeToContainerIndex = rhs.typeToContainerIndex;

            for (auto it = container.begin(); it != container.end(); ++it)
            {
                BaseType *clonedElement = static_cast<BaseType *>(it->element->Clone());
                it->element = clonedElement;
            }
            return *this;
        }

        TypeMapWithPriority &operator=(TypeMapWithPriority &&rhs) noexcept
        {
            DeleteElements();
            container = std::move(rhs.container);
            typeToContainerIndex = std::move(rhs.typeToContainerIndex);
            rhs.container.clear();
            rhs.typeToContainerIndex.clear();
            return *this;
        }

        ~TypeMapWithPriority()
        {
            Clear();
        }

    public:
        template<typename Type, typename... Args, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        Type *const EmplaceWithPriority(size_t priority, Args&&... args)
        {
            Type *element = new Type(std::forward<Args>(args)...);
            AddInner<Type>(element, priority);
            return element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        Type *const EmplaceWithPriority(size_t priority)
        {
            Type *element = new Type();
            AddInner<Type>(element, priority);
            return element;
        }

        template<typename Type, typename... Args, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        Type *const Emplace(Args&&... args)
        {
            Type *element = new Type(std::forward<Args>(args)...);
            AddInner<Type>(element, element->GetDefaultPriority());
            return element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        Type *const Emplace()
        {
            Type *element = new Type();
            AddInner<Type>(element, element->GetDefaultPriority());
            return element;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        void AddWithPriority(size_t priority, Type *element)
        {
            if (!element)
            {
                LOG_ERROR("Element is null");
                return;
            }

            AddInner<Type>(element, priority);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        void Add(Type *element)
        {
            if (!element)
            {
                LOG_ERROR("Element is null");
                return;
            }

            AddInner<Type>(element, element->GetDefaultPriority());
        }

    private:
        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
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

            if (pos == container.end())
            {
                container.push_back(std::move(containerElement));
                typeToContainerIndex.emplace(type, container.size() - 1);
            }
            else
            {
                pos = container.insert(pos, std::move(containerElement));
                typeToContainerIndex.emplace(type, pos - container.begin());
                UpdateTypeToIndex(pos + 1);
            }
        }

    private:
        bool CheckElementForNotNull(BaseType *element) const
        {
            if (!element)
            {
                LOG_ERROR("Element is null");
                return false;
            }

            return true;
        }

        bool CheckContainerIteratorIsNotEnd(auto it) const
        {
            if (it == container.end())
            {
                LOG_ERROR("Container doesn't have such element");
                return false;
            }

            return true;
        }

        const auto FindContainerIterator(BaseType *element) const
        {
            if (!CheckElementForNotNull(element))
            {
                return container.end();
            }

            auto pos = std::find_if(container.begin(), container.end(),
                [element](const ContainerElement &containerElement) { return containerElement.element == element; }
            );

            return pos;
        }

        auto FindContainerIterator(BaseType *element)
        {
            if (!CheckElementForNotNull(element))
            {
                return container.end();
            }

            auto pos = std::find_if(container.begin(), container.end(),
                [element](const ContainerElement &containerElement) { return containerElement.element == element; }
            );

            return pos;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        const auto FindContainerIterator() const
        {
            return container.begin() + GetIndex<Type>();
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        auto FindContainerIterator()
        {
            return container.begin() + GetIndex<Type>();
        }

        const auto FindContainerIterator(const std::type_index &type) const
        {
            return container.begin() + GetIndex(type);
        }

        auto FindContainerIterator(const std::type_index &type)
        {
            return container.begin() + GetIndex(type);
        }

        const ContainerElement &GetContainerElement(BaseType *element) const
        {

            auto pos = FindContainerIterator(element);
            CheckContainerIteratorIsNotEnd(pos);
            return *pos;
        }

        ContainerElement &GetContainerElement(BaseType *element)
        {

            auto pos = FindContainerIterator(element);
            CheckContainerIteratorIsNotEnd(pos);
            return *pos;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        const ContainerElement &GetContainerElement() const
        {
            auto pos = FindContainerIterator<Type>();
            CheckContainerIteratorIsNotEnd(pos);
            return *pos;
        }

        const ContainerElement &GetContainerElement(const std::type_index &type) const
        {
            auto pos = FindContainerIterator(type);
            CheckContainerIteratorIsNotEnd(pos);
            return *pos;
        }

        size_t const GetIndex(BaseType *element) const
        {
            auto pos = FindContainerIterator(element);
            CheckContainerIteratorIsNotEnd(pos);
            return pos - container.begin();
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        size_t const GetIndex() const
        {
            return typeToContainerIndex.at(std::type_index(typeid(Type)));
        }

        size_t const GetIndex(const std::type_index &type) const
        {
            return typeToContainerIndex.at(type);
        }

    public:
        bool Contains(BaseType *element) const
        {
            auto pos = FindContainerIterator(element);
            return pos != container.end();
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        bool Contains() const
        {
            return typeToContainerIndex.contains(std::type_index(typeid(Type)));
        }

        bool Contains(const std::type_index &type) const
        {
            return typeToContainerIndex.contains(type);
        }

        void Remove(BaseType *element)
        {
            auto pos = FindContainerIterator(element);
            Remove(pos);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        void Remove()
        {
            auto pos = FindContainerIterator<Type>();
            Remove(pos);
        }

        void Remove(const std::type_index &type)
        {
            auto pos = FindContainerIterator(type);
            Remove(pos);
        }

        void Remove(auto it)
        {
            delete it->element;
            typeToContainerIndex.erase(it->type);
            it = container.erase(it);
            UpdateTypeToIndex(it);
        }
        
        size_t const GetPriority(BaseType* element) const
        {
            const ContainerElement &containerElement = GetContainerElement(element);
            return containerElement.prioirity;
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
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

        size_t const GetOrder(BaseType *element) const
        {
            return GetIndex(element);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        size_t const GetOrder() const
        {
            return GetIndex<Type>();
        }

        size_t const GetOrder(const std::type_index &type) const
        {
            return GetIndex(type);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
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

        void SetPriority(BaseType *element, size_t priority)
        {
            auto pos = FindContainerIterator(element);
            SetPriority(pos, priority);
        }

        template<typename Type, typename = std::enable_if_t<std::is_base_of_v<BaseType, Type> || std::is_same_v<BaseType, Type>>>
        void SetPriority(size_t priority)
        {
            auto pos = FindContainerIterator<Type>();
            SetPriority(pos, priority);
        }

        void SetPriority(const std::type_index &type, size_t priority)
        {
            auto pos = FindContainerIterator(type);
            SetPriority(pos, priority);
        }

        void SetPriority(auto it, size_t priority)
        {
            if (it->priority == priority)
            {
                return;
            }

            size_t previousPriority = it->priority;
            it->priority = priority;

            if (previousPriority < priority)
            {
                auto end = SortAfterPriorityIncreasingOfOneElement(it);
                UpdateTypeToIndex(it, end + 1);
            }
            else
            {
                auto begin = SortAfterPriorityDecreasingOfOneElement(it);
                UpdateTypeToIndex(begin, it + 1);
            }
        }

    private:
        bool CheckItExistInContainer(auto it) const
        {
            if (it < container.begin() || it >= container.end())
            {
                LOG_ERROR("Can't update order after the end of container");
                return false;
            }

            return true;
        }

        bool CheckEndItExistInContainer(auto it) const
        {
            if (it < container.begin() || it > container.end())
            {
                LOG_ERROR("Can't update order after the end of container");
                return false;
            }

            return true;
        }

        void UpdateTypeToIndex(auto start)
        {
            UpdateTypeToIndex(start, container.end());
        }

        void UpdateTypeToIndex(auto start, auto end)
        {
            if (start >= end)
            {
                return;
            }

            CheckItExistInContainer(start);
            CheckEndItExistInContainer(end);
            for (auto it = start; it != end; ++it)
            {
                typeToContainerIndex[it->type] = it - container.begin();
            }
        }

        auto SortAfterPriorityIncreasingOfOneElement(auto it)
        {
            CheckItExistInContainer(it);
            auto changedElementIt = it;
            auto nextElementIt = changedElementIt + 1;
            const size_t changedElementPriority = changedElementIt->priority;
            while (nextElementIt != container.end() && changedElementPriority > nextElementIt->priority)
            {
                std::iter_swap(changedElementIt, nextElementIt);
                changedElementIt = nextElementIt;
                nextElementIt = changedElementIt + 1;
            }

            return changedElementIt;
        }

        auto SortAfterPriorityDecreasingOfOneElement(auto it)
        {
            CheckItExistInContainer(it);
            auto changedElementIt = it;
            auto nextElementIt = changedElementIt - 1;
            const size_t changedElementPriority = changedElementIt->priority;

            while (nextElementIt != container.begin() && changedElementPriority < nextElementIt->priority)
            {
                std::iter_swap(changedElementIt, nextElementIt);
                changedElementIt = nextElementIt;
                nextElementIt = changedElementIt - 1;
            }

            if (changedElementPriority < nextElementIt->priority)
            {
                std::iter_swap(changedElementIt, nextElementIt);
                changedElementIt = nextElementIt;
            }

            return changedElementIt;
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