#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>


namespace Engine
{
    class TimeModule final
    {
    public:
        TimeModule();

    private:
        TimeModule(const TimeModule &timeModule) = delete;
        TimeModule(TimeModule &&timeModule) = delete;
        TimeModule &operator=(const TimeModule &rhs) = delete;
        TimeModule &operator=(TimeModule &&rhs) = delete;

    public:
        void Update();
        float GetTime();
        float GetDeltaTime();

    private:
        float deltaTime;
        float globalTime;
    };
}