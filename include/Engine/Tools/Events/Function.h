#pragma once

#include "FunctionIdGetter.h"
#include <functional>

namespace Engine::Tools::Events
{
	template<typename ParamIn>
	class Function
	{
	public:
		typedef ParamIn T;
		typedef std::function<void(T)> StdFunction;

	protected:
		Function() {}

	public:
		Function(StdFunction function)
			: function(function),
			id(FunctionIdGetter<T>::GetNextId())
		{}

		Function(const Function &rhs)
			: function(rhs.function),
			id(rhs.id)
		{}

		Function(Function &&rhs) noexcept
			: function(std::move(rhs.function)),
			id(rhs.id)
		{
			rhs.id = 0;
		}

		Function &operator=(const Function &rhs)
		{
			this->function = rhs.function;
			this->id = rhs.id;
			return *this;
		}

		Function &operator=(Function &&rhs) noexcept
		{
			this->function = std::move(rhs.function);
			this->id = rhs.id;
			rhs.id = 0;
			return *this;
		}

	public:
		template<typename T_ = T, typename = std::enable_if_t<!std::is_void_v<T_>>>
		void operator()(const T_ &value)
		{
			Call(value);
		}

		template<typename T_ = T, typename = std::enable_if_t<!std::is_void_v<T_>>>
		void Call(const T_ &value)
		{
			function(value);
		}

		template<typename T_ = T, typename = std::enable_if_t<std::is_void_v<T_>>>
		void operator()()
		{
			Call();
		}

		template<typename T_ = T, typename = std::enable_if_t<std::is_void_v<T_>>>
		void Call()
		{
			function();
		}

		size_t GetId() const { return id; }

	protected:
		StdFunction function;
		size_t id;
	};
}