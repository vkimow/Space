#pragma once

#include <functional>
#include <unordered_map>
#include "Function.h"

namespace Engine::Tools::Events
{
#pragma region Create Macros
#define CREATE_ACTION(type, name)\
	public:\
\
		void AddListener##name(const Engine::Tools::Events::Function<type>& function)\
		{\
			##name += function;\
		}\
\
		void RemoveListener##name(const Engine::Tools::Events::Function<type>& function)\
		{\
			##name -= function;\
		}\
\
		void AddListener##name(Engine::Tools::Events::Action<type>* const function)\
		{\
			##name += function;\
		}\
\
		void RemoveListener##name(const Engine::Tools::Events::Action<type>* const function)\
		{\
			##name -= function;\
		}\
\
	private:\
		Engine::Tools::Events::Action<type> ##name;
#pragma endregion

    template <typename ParamIn>
    class Action
    {
    private:
        typedef ParamIn T;
        typedef Function<T> FunctionType;

    public:
        Action()
            : functionListeners()
            , actionListeners()
            , id(FunctionIdGetter<Action>::GetNextId())
        {};

        ~Action() {};

        Action(const Action &rhs)
            : functionListeners(rhs.functionListeners)
            , actionListeners(rhs.actionListeners)
            , id(rhs.id)
        {}

        Action(Action &&rhs) noexcept
            : functionListeners(std::move(rhs.functionListeners))
            , actionListeners(std::move(rhs.actionListeners))
            , id(std::move(rhs.id))
        {}

        Action(const FunctionType &listener)
            : Action()
        {
            AddListener(listener);
        };

        Action(FunctionType &&listener)
            : Action()
        {
            AddListener(std::move(listener));
        };

        Action &operator=(const Action &rhs)
        {
            functionListeners = rhs.functionListeners;
        };

        Action &operator=(Action &&rhs) noexcept
        {
            functionListeners = std::move(rhs.functionListeners);
        };

        Action &operator=(const FunctionType &rhs)
        {
            functionListeners.clear();
            AddListener(rhs);
        };

        Action &operator=(FunctionType &&rhs)
        {
            functionListeners.clear();
            AddListener(std::move(rhs));
        };

    public:
        Action &operator+=(const FunctionType &rhs) { AddListener(rhs); return *this; }
        Action &operator+=(Action *const rhs) { AddListener(rhs); return *this; }

        Action &operator-=(const FunctionType &rhs) { RemoveListener(rhs); return *this; }
        Action &operator-=(const Action *const rhs) { RemoveListener(rhs); return *this; }

        template<typename T_ = T, typename = std::enable_if_t<!std::is_void_v<T_>>>
        void operator()(const T_ &value) { RiseEvent(value); }

        template<typename T_ = T, typename = std::enable_if_t<std::is_void_v<T_>>>
        void operator()() { RiseEvent(); }

    private:
        void RemoveListener(const FunctionType &listener)
        {
            RemoveFunctionListener(listener.GetId());
        }

        void RemoveListener(const Action *const listener)
        {
            RemoveActionListener(listener->GetId());
        }

        void RemoveFunctionListener(size_t id)
        {
            if (functionListeners.find(id) == functionListeners.end())
            {
                throw std::exception("Doesn't contain this listener");
            }

            functionListeners.erase(id);
        }

        void RemoveActionListener(size_t id)
        {
            if (actionListeners.find(id) == actionListeners.end())
            {
                throw std::exception("Doesn't contain this listener");
            }

            actionListeners.erase(id);
        }

        void AddListener(const FunctionType &listener)
        {
            if (functionListeners.find(listener.GetId()) != functionListeners.end())
            {
                throw std::exception("Already contain this listener");
            }

            auto pair = std::make_pair(listener.GetId(), listener);
            functionListeners.insert(std::move(pair));
        }

        void AddListener(Action *const listener)
        {
            if (actionListeners.find(listener->GetId()) != actionListeners.end())
            {
                throw std::exception("Already contain this listener");
            }

            std::pair<size_t, Action *const> pair = std::make_pair(listener->GetId(), listener);
            actionListeners.insert(std::move(pair));
        }


        template<typename T_ = T, typename = std::enable_if_t<std::is_void_v<T_>>>
        void RiseEvent()
        {
            for (auto &listener : actionListeners)
            {
                listener.second->RiseEvent();
            }

            for (auto &listener : functionListeners)
            {
                listener.second.Call();
            }
        }

        template<typename T_ = T, typename = std::enable_if_t<!std::is_void_v<T_>>>
        void RiseEvent(const T_ &value)
        {
            for (auto &listener : actionListeners)
            {
                listener.second->RiseEvent(value);
            }

            for (auto &listener : functionListeners)
            {
                listener.second.Call(value);
            }
        }

    public:
        size_t GetId() const { return id; };

    private:
        std::unordered_map<size_t, FunctionType> functionListeners;
        std::unordered_map<size_t, Action *const> actionListeners;
        size_t id;
    };
}