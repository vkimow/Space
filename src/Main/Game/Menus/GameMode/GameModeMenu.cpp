#include "Game/Menus/GameMode/GameModeMenu.h"
#include "Game/Menus/GameMode/GameModeMenuUI.h"
#include "Game/GameManager.h"

namespace Main::Game
{
    GameModeMenu::GameModeMenu(GameManager *gameManager)
        : Menu("GameMode", new GameModeMenuUI(this))
        , gameManager(gameManager)
        , setGameMode(this, &GameModeMenu::SetGameMode)
    {
        mode = gameManager->GetGameModeType();
        gameManager->AddListenerOnGameModeChanged(setGameMode);
    }

    GameModeMenu::~GameModeMenu()
    {
        gameManager->RemoveListenerOnGameModeChanged(setGameMode);
    }

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
        mode = value;
        gameManager->SetGameMode(value);
    }
}