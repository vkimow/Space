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
    template<typename KeyType, typename ValueType>
    class MapWithPriority
    {
    private:
        struct ContainerElement
        {
            KeyType key;
            ValueType *element;
            size_t priority;
        };

    public:
        MapWithPriority()
            : container()
            , keyToContainerIndex()
        {}

        MapWithPriority(size_t size)
            : container(size)
            , keyToContainerIndex(size)
        {}

        template<typename Value = ValueType> 
        MapWithPriority(const MapWithPriority &rhs)
            : container(rhs.container)
            , keyToContainerIndex(rhs.keyToContainerIndex)
        {
            for (auto it = container.begin(); it != container.end(); ++it)
            {
                Value *clonedElement = static_cast<Value *>(it->element->Clone());
                it->element = clonedElement;
            }
        }

        MapWithPriority(MapWithPriority &&rhs) noexcept
            : container(std::move(rhs.container))
            , keyToContainerIndex(std::move(rhs.keyToContainerIndex))
        {
            rhs.container.clear();
            rhs.keyToContainerIndex.clear();
        }

        template<typename Value = ValueType>
        MapWithPriority &operator=(const MapWithPriority &rhs)
        {
            DeleteElements();
            container = rhs.container;
            keyToContainerIndex = rhs.keyToContainerIndex;

            for (auto it = container.begin(); it != container.end(); ++it)
            {
                Value *clonedElement = static_cast<Value *>(it->element->Clone());
                it->element = clonedElement;
            }
            return *this;
        }

        MapWithPriority &operator=(MapWithPriority &&rhs) noexcept
        {
            DeleteElements();
            container = std::move(rhs.container);
            keyToContainerIndex = std::move(rhs.keyToContainerIndex);
            rhs.container.clear();
            rhs.keyToContainerIndex.clear();
            return *this;
        }

        ~MapWithPriority()
        {
            Clear();
        }

    public:
        template<typename Type = ValueType, typename... Args, typename = std::enable_if_t<std::is_base_of_v<ValueType, Type> || std::is_same_v<ValueType, Type>>>
        Type *const Emplace(const KeyType &key, size_t priority, Args&&... args)
        {
            Type *element = new Type(std::forward<Args>(args)...);
            AddInner(key, element, priority);
            return element;
        }

        template<typename Type = ValueType, typename = std::enable_if_t<std::is_base_of_v<ValueType, Type> || std::is_same_v<ValueType, Type>>>
        Type *const Emplace(const KeyType &key, size_t priority)
        {
            Type *element = new Type();
            AddInner(key, element, priority);
            return element;
        }

        void Add(const KeyType &key, size_t priority, ValueType *element)
        {
            if (!element)
            {
                LOG_ERROR("Element is null");
                return;
            }

            AddInner(key, element, priority);
        }

    private:
        void AddInner(const KeyType &key, ValueType *element, size_t priority)
        {
            if (keyToContainerIndex.contains(key))
            {
                LOG_ERROR("Already contains element with this key");
                return;
            }

            ContainerElement containerElement(key, element, priority);

            auto pos = std::find_if(container.begin(), container.end(),
                [priority](const ContainerElement &containerElement) { return containerElement.priority > priority; }
            );

            if (pos == container.end())
            {
                container.push_back(std::move(containerElement));
                keyToContainerIndex.emplace(key, container.size() - 1);
            }
            else
            {
                pos = container.insert(pos, std::move(containerElement));
                keyToContainerIndex.emplace(key, pos - container.begin());
                UpdateTypeToIndex(pos + 1);
            }
        }

        bool CheckElementForNotNull(ValueType *element) const
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

        const auto FindContainerIterator(const KeyType &key) const
        {
            return container.begin() + GetIndex(key);
        }

        auto FindContainerIterator(const KeyType &key)
        {
            return container.begin() + GetIndex(key);
        }

        const ContainerElement &GetContainerElement(const KeyType &key) const
        {
            size_t index = GetIndex(key);
            return container[index];
        }

        ContainerElement &GetContainerElement(const KeyType &key)
        {
            size_t index = GetIndex(key);
            return container[index];
        }

        size_t const GetIndex(const KeyType &key) const
        {
            return keyToContainerIndex.at(key);
        }

        const auto FindContainerIterator(ValueType *element) const
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

        auto FindContainerIterator(ValueType *element)
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

        const ContainerElement &GetContainerElement(ValueType *element) const
        {
            auto pos = FindContainerIterator(element);
            CheckContainerIteratorIsNotEnd(pos);
            return *pos;
        }

        ContainerElement &GetContainerElement(ValueType *element)
        {
            auto pos = FindContainerIterator(element);
            CheckContainerIteratorIsNotEnd(pos);
            return *pos;
        }

        size_t const GetIndex(ValueType *element) const
        {
            auto pos = FindContainerIterator(element);
            CheckContainerIteratorIsNotEnd(pos);
            return pos - container.begin();
        }

    public:
        bool Contains(const KeyType &key) const
        {
            return keyToContainerIndex.contains(key);
        }

        bool Contains(ValueType *value) const
        {
            auto pos = FindContainerIterator(value);
            return pos != container.end();
        }

        void Remove(const KeyType &key)
        {
            auto pos = FindContainerIterator(key);
            Remove(pos);
        }

        void Remove(ValueType *element)
        {
            auto pos = FindContainerIterator(element);
            Remove(pos);
        }

        void Remove(auto it)
        {
            delete it->element;
            keyToContainerIndex.erase(it->key);
            it = container.erase(it);
            UpdateTypeToIndex(it);
        }

        size_t const GetPriority(const KeyType &key) const
        {
            const ContainerElement &containerElement = GetContainerElement(key);
            return containerElement.priority;
        }

        size_t const GetPriority(ValueType *element) const
        {
            const ContainerElement &containerElement = GetContainerElement(element);
            return containerElement.priority;
        }

        size_t const GetOrder(const KeyType &key) const
        {
            return GetIndex(key);
        }

        size_t const GetOrder(ValueType *element) const
        {
            return GetIndex(element);
        }

        ValueType *const Get(const KeyType &key) const
        {
            const ContainerElement &containerElement = GetContainerElement(key);
            return containerElement.element;
        }

        void SetPriority(const KeyType &key, size_t priority)
        {
            auto pos = FindContainerIterator(key);
            SetPriority(pos, priority);
        }

        void SetPriority(ValueType *element, size_t priority)
        {
            auto pos = FindContainerIterator(element);
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
                keyToContainerIndex[it->key] = it - container.begin();
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
        size_t Size() const { return container.size(); }

    public:
        auto begin() { return container.begin(); }
        auto end() { return container.end(); }
        auto begin() const { return container.begin(); }
        auto end() const { return container.end(); }


        void Clear()
        {
            DeleteElements();
            container.clear();
            keyToContainerIndex.clear();
        }

    private:
        std::vector<ContainerElement> container;
        std::unordered_map<KeyType, size_t> keyToContainerIndex;
    };
}