#pragma once

#include <type_traits>
#include <functional>

namespace Engine::Tools::Events
{
    template<typename Type>
    class FunctionIdGetter
    {
    public:
        static size_t GetNextId() { return instanceCounter++; }

    private:
        static size_t instanceCounter;
    };

    template<typename Type>
    size_t FunctionIdGetter<Type>::instanceCounter = 1; // counter starts with 1. 0 is index for disposed functions
}