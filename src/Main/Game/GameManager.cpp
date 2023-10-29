#include "Game/GameManager.h"
#include "Game/GameHeader.h"

namespace Main::Game
{
    GameManager::GameManager(Engine::Window *window, Engine::Engine *engine)
        : window(window)
        , engine(engine)
        , scene(nullptr)
        , gameModeType(EGameMode::Edit)
        , gameMode(nullptr)
        , gameModes()
    {
        auto &menuContainer = engine->GetUI()->GetMenuManager()->GetContainer();
        auto gameModeMenu = menuContainer.Create<GameModeMenu>(this);
        gameModeMenu->SetActive(true);

        scene = new Main::Game::MainScene("Main", window, engine);
        auto space = new Space::SpaceMode(engine->GetUI());
        auto edit = new Editor::EditorMode(engine->GetUI(), engine->GetGraphics()->GetRenderManager());
        space->SetScene(scene);
        edit->SetScene(scene);

        gameModes.Add<Space::SpaceMode>(space);
        gameModes.Add<Editor::EditorMode>(edit);
        SetGameMode(EGameMode::Edit);
    }

    GameManager::~GameManager()
    {
        auto &menuContainer = engine->GetUI()->GetMenuManager()->GetContainer();
        menuContainer.Remove<GameModeMenu>();

        delete scene;
    }

    void GameManager::Update()
    {
        gameMode->Update();
    }

    void GameManager::SetGameMode(EGameMode value)
    {
        if (gameMode)
        {
            gameMode->End();
        }

        switch (value)
        {
            case EGameMode::Space:
            {
                gameMode = gameModes.Get<Space::SpaceMode>();
                LOG_DEBUG("Enter Play Mode");
                break;
            }
            case EGameMode::Edit:
            {
                gameMode = gameModes.Get<Editor::EditorMode>();
                LOG_DEBUG("Enter Edit Mode");
                break;
            }
        }

        gameMode->Start();
        gameModeType = value;
    }

    EGameMode GameManager::GetGameModeType() const
    {
        return gameModeType;
    }
}