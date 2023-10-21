#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include "Function.h"

namespace Engine::Tools::Events
{
	template <typename Type>
	class GlobalFunction: public Function<Type>
	{
	public:
		typedef Type T;
		typedef void(*FunctionPointer)(T);
		typedef std::function<void(Type)> StdFunction;
		typedef std::unordered_map<FunctionPointer, GlobalFunction> GlobalFunctionsMap;

#pragma region Constructors
	private:
		GlobalFunction(StdFunction function)
			: Function<Type>(std::move(function))
		{}

	public:
		GlobalFunction() {}

		GlobalFunction(const GlobalFunction &rhs)
			: Function<Type>(rhs)
		{}

		GlobalFunction(GlobalFunction &&rhs) noexcept
			: Function<Type>(std::move(rhs))
		{}

		GlobalFunction &operator=(const GlobalFunction &rhs) 
		{
			return Function<Type>::operator=(rhs);
		}
		GlobalFunction &operator=(GlobalFunction &&rhs) noexcept 
		{
			return Function<Type>::operator=(std::move(rhs));
		}

	public:
		GlobalFunction(FunctionPointer function)
		{
			if (ContainsGlobalFunction(function))
			{
				auto referenceFunction = GetGlobalFunction(function);
				this->function = referenceFunction.function;
				this->id = referenceFunction.id;
				return;
			}

			auto stdFunction = std::function(function);
			this->function = stdFunction;
			this->id = FunctionIdGetter<T>::GetNextId();

			AddGlobalFunction(function, *this);
		}
#pragma endregion

	private:
		static bool ContainsGlobalFunction(FunctionPointer function)
		{
			return globalFunctions.find(function) != globalFunctions.end();
		}

		static void AddGlobalFunction(FunctionPointer function, const GlobalFunction &globalFunction)
		{
			auto pair = std::make_pair(function, globalFunction);
			globalFunctions.insert(std::move(pair));
		}

		static const GlobalFunction &GetGlobalFunction(FunctionPointer function)
		{
			if (!ContainsGlobalFunction(function))
			{
				throw std::exception("Have no function!");
			}

			return globalFunctions[function];
		}

	private:
		static GlobalFunctionsMap globalFunctions;
	};

	template<typename Type>
	std::unordered_map<void(*)(Type), GlobalFunction<Type>> GlobalFunction<Type>::globalFunctions = { };
}