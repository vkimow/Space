#pragma once

#include <vector>
#include <memory>

namespace Game
{
    class App;
}

namespace Engine
{
    class TimeModule final
    {
        friend class Game::App;
        friend class Engine;

    private:
        TimeModule();
        TimeModule(const TimeModule &rhs) = delete;
        TimeModule(TimeModule &&rhs) = delete;
        TimeModule &operator=(const TimeModule &rhs) = delete;
        TimeModule &operator=(TimeModule &&rhs) = delete;

    private:
        void Update();

    public:
        static float GetGlobalTime();
        static float GetDeltaTime();

    private:
        static float deltaTime;
        static float globalTime;
    };
}