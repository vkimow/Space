#include "Game/Menus/GameMode/GameModeMenuUI.h"
#include "Game/Menus/GameMode/GameModeMenu.h"
#include <imgui.h>

namespace Main::Game
{
    GameModeMenuUI::GameModeMenuUI(GameModeMenu *const menu)
        : MenuUI(menu)
    {}

    void GameModeMenuUI::UpdateInner()
    {
        GameModeMenu *menu = GetMenu<GameModeMenu>();
        switch (menu->GetGameMode())
        {
            case EGameMode::Space:
            {
                if (ImGui::Button("Enter Edit Mode"))
                {
                    menu->SetGameMode(EGameMode::Edit);
                }
                break;
            }
            case EGameMode::Edit:
            {
                if (ImGui::Button("Enter Play Mode"))
                {
                    menu->SetGameMode(EGameMode::Space);
                }
                break;
            }
        }
    }
}