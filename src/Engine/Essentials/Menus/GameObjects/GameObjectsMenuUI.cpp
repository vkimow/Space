#include "Engine/Essentials/Menus/GameObjects/GameObjectsMenuUI.h"
#include "Engine/Essentials/Menus/GameObjects/GameObjectsMenu.h"
#include <imgui.h>

namespace Engine::UI
{
    GameObjectsMenuUI::GameObjectsMenuUI(GameObjectsMenu *const menu)
        : MenuUI(menu)
    {}

    void GameObjectsMenuUI::UpdateInner()
    {
        GameObjectsMenu *const menu = GetMenu<GameObjectsMenu>();
        const std::unordered_map<std::string, Objects::GameObject*>& nameToGameObjects = menu->scene->GetGameObjects();

        for (auto it = nameToGameObjects.begin(); it != nameToGameObjects.end(); ++it)
        {
            if (ImGui::Button(it->first.c_str()))
            {
                menu->SetTargetForEditor(it->second);
            }
        }
    }
}