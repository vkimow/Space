#pragma once

namespace Engine::Tools::Interfaces
{
    class IClonable
    {
    public:
        virtual IClonable *Clone() = 0;
    };
}