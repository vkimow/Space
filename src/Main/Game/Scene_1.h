#pragma once

#include "Engine/Main/EngineHeader.h"

namespace Game
{
    class Scene_1 final: public Engine::Objects::Scene
    {
    public:
        Scene_1(const std::string &name, Engine::Window *const window, Engine::Engine *const engine);
        ~Scene_1();

    public:
        virtual void Update() override;
        virtual void Render() override;
    };
}