#pragma once

#include "Engine/Objects/Scene.h"

namespace Main::Game
{
    class IGameMode
    {
    public:
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void End() = 0;

    public:
        virtual void SetScene(Engine::Objects::Scene *value) = 0;
    };
}