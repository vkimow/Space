#pragma once

#include "Engine/Main/EngineHeader.h"
#include "Space/SpaceHeader.h"

namespace Main::Game
{
    class TestScene final: public Engine::Objects::Scene
    {
    public:
        TestScene(const std::string &name, Engine::Window *const window, Engine::Engine *const engine, Space::SpaceManager *const space);
        ~TestScene();

    public:
        virtual void Update() override;
        virtual void Render() override;

    private:
        Space::SpaceManager *space;
    };
}