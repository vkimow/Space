#pragma once

#include "Engine/Main/EngineHeader.h"

namespace Main::Game
{
    class MainScene final: public Engine::Objects::Scene
    {
    public:
        MainScene(const std::string &name, Engine::Window *const window, Engine::Engine *const engine);
        ~MainScene();

    public:
        virtual void Update() override;
        virtual void Render() override;
    };
}