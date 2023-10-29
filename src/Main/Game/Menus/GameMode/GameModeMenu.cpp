#include "Game/Menus/GameMode/GameModeMenu.h"
#include "Game/Menus/GameMode/GameModeMenuUI.h"
#include "Game/GameManager.h"

namespace Main::Game
{
    GameModeMenu::GameModeMenu(GameManager *gameManager)
        : Menu("GameMode", new GameModeMenuUI(this))
        , gameManager(gameManager)
    {}

    GameModeMenu::~GameModeMenu()
    {}

    void GameModeMenu::Update()
    {
        UpdateUI();
    }

    size_t GameModeMenu::GetDefaultPriority() const
    {
        return priority;
    }

    void GameModeMenu::SetGameMode(EGameMode value)
    {
        if (gameManager->GetGameModeType() != value) 
        {
            gameManager->SetGameMode(value);
        }
    }

    EGameMode GameModeMenu::GetGameMode() const
    {
        return gameManager->GetGameModeType();
    }
}