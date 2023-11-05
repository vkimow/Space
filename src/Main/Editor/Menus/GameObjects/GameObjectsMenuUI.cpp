#include "Editor/Menus/GameObjects/GameObjectsMenuUI.h"
#include "Editor/Menus/GameObjects/GameObjectsMenu.h"
#include "Editor/GameObjectManager.h"
#include <imgui.h>

namespace Main::Editor
{
    GameObjectsMenuUI::GameObjectsMenuUI(GameObjectsMenu *const menu)
        : MenuUI(menu, 200.0f, 700.0f)
    {}

    void GameObjectsMenuUI::UpdateInner()
    {
        GameObjectsMenu *const menu = GetMenu<GameObjectsMenu>();
        auto& gameObjects = menu->objectsManager->GetGameObjects();

        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        {
            if (it->element->IsInvisible())
            {
                continue;
            }

            if (ImGui::Button(it->key.c_str()))
            {
                menu->SetTarget(it->element);
            }
        }
    }
}