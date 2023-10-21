#include "Engine/Main/Modules/TimeModule.h"
#include <GLFW/glfw3.h>

namespace Engine
{
    float TimeModule::globalTime = glfwGetTime();
    float TimeModule::deltaTime = 0;

    TimeModule::TimeModule()
    {
        Update();
    }

    void TimeModule::Update()
    {
        float now = glfwGetTime();
        deltaTime = globalTime - now;
        globalTime = now;
    }

    float TimeModule::GetGlobalTime()
    {
        return globalTime;
    }

    float TimeModule::GetDeltaTime()
    {
        return deltaTime;
    }
}
