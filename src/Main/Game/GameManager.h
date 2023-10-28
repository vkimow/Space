#pragma once
#include "Engine/Main/EngineHeader.h"
#include "Game/Modes/IGameMode.h"
#include "Game/Modes/EGameMode.h"

namespace Main
{
    class App;
}

namespace Main::Game
{
    class GameManager
    {
        friend class App;
        GameManager(Engine::Window *window, Engine::Engine *engine);
        GameManager(const GameManager &rhs) = delete;
        GameManager(GameManager &&rhs) = delete;
        GameManager &operator=(const GameManager &rhs) = delete;
        GameManager &operator=(GameManager &&rhs) = delete;
        ~GameManager();

    private:
        void Update();

    public:
        void SetGameMode(EGameMode mode);
        EGameMode GetGameModeType() const;

    private:
        Engine::Window *const window;
        Engine::Engine *const engine;
        Engine::Objects::Scene *scene;
        EGameMode modeType;
        IGameMode *mode;

    public:
        CREATE_ACTION(EGameMode, OnGameModeChanged);
    };
}