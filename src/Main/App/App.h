#pragma once
#include <string>
#include "Engine/Main/EngineHeader.h"
#include "Game/GameHeader.h"

namespace Main
{
    class App
    {
    public:
        App();
        App(Engine::Objects::Scene *const scene);


        App(const App &rhs) = delete;
        App(App &&rhs) = delete;
        ~App();

    public:
        void Start();

    private:
        bool ShouldExit();

    private:
        Engine::Window window;
        Engine::Engine engine;
        Game::GameManager gameManager;
    };
}
