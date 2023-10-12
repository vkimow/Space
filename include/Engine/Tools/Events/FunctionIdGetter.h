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
    size_t FunctionIdGetter<Type>::instanceCounter = 0;
}