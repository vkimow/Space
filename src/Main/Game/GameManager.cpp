#include "Game/GameManager.h"
#include "Game/GameHeader.h"

namespace Main::Game
{
    GameManager::GameManager(Engine::Window *window, Engine::Engine *engine)
        : window(window)
        , engine(engine)
        , scene(nullptr)
        , modeType(EGameMode::Play)
        , mode(nullptr)
    {
        engine->GetUI()->GetMenuManager()->GetContainer().Create<GameModeMenu>(this);
        scene = new Main::Game::MainScene("Main", window, engine);
    }

    GameManager::~GameManager()
    {
        delete scene;
    }

    void GameManager::Update()
    {
        scene->Update();
    }

    void GameManager::SetGameMode(EGameMode mode)
    {
        switch (mode)
        {
            case EGameMode::Play:
            {
                LOG_DEBUG("Enter Play Mode");
                break;
            }
            case EGameMode::Edit:
            {
                LOG_DEBUG("Enter Edit Mode");
                break;
            }
        }
        modeType = mode;
        OnGameModeChanged(mode);
    }

    EGameMode GameManager::GetGameModeType() const
    {
        return modeType;
    }
}