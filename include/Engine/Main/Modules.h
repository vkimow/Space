#pragma once

#include "Engine/Main/Modules/TimeModule.h"
#include "Engine/Main/Modules/InputModule.h"
#include "Engine/Main/Modules/GraphicsModule.h"


namespace Engine
{
    class Modules
    {
        friend class Engine;

    private:
        Modules() = delete;
        Modules(GLFWwindow* window);
        ~Modules() = default;

    public:
        GraphicsModule& GetGraphics();
        TimeModule &GetTime();
        InputModule &GetInput();


    private:
        GraphicsModule graphics;
        TimeModule time;
        InputModule input;
    };
}