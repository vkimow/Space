#include "Engine/Main/Modules/TimeModule.h"

namespace Engine
{
    TimeModule::TimeModule()
        : globalTime(glfwGetTime())
        , deltaTime(0)
    {}

    void TimeModule::Update()
    {
        float now = glfwGetTime();
        deltaTime = globalTime - now;
        globalTime = globalTime;
    }

    float TimeModule::GetTime()
    {
        return globalTime;
    }

    float TimeModule::GetDeltaTime()
    {
        return deltaTime;
    }
}
