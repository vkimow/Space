#include "Engine/Main/Modules/TimeModule.h"
#include <GLFW/glfw3.h>

namespace Engine
{
    float TimeModule::globalTime = static_cast<float>(glfwGetTime());
    float TimeModule::deltaTime = 0;

    TimeModule::TimeModule()
    {
        Update();
    }

    void TimeModule::Update()
    {
        float now = static_cast<float>(glfwGetTime());
        deltaTime = now - globalTime;
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
