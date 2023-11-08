#pragma once
#include "Engine/Main/EngineHeader.h"
#include "Game/Mode/ModesHeader.h"
#include "Space/SpaceHeader.h"
#include "Editor/EditorHeader.h"

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
        void SetGameMode(EGameMode value);
        EGameMode GetGameModeType() const;

    public:
        CREATE_ACTION(EGameMode, OnGameModeChanged);

    private:
        Engine::Window *const window;
        Engine::Engine *const engine;
        Engine::Objects::Scene *scene;

        EGameMode gameModeType;
        IGameMode *gameMode;
        Engine::Tools::Structs::TypeMapUnordered<IGameMode> gameModes;

    };
}