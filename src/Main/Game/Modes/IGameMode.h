#pragma once

namespace Main::Game
{
    class IGameMode
    {
    public:
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void End() = 0;
    };
}