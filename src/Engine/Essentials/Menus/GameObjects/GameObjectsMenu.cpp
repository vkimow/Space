#include "Engine/Essentials/Menus/GameObjects/GameObjectsMenu.h"
#include "Engine/Essentials/Menus/GameObjects/GameObjectsMenuUI.h"

namespace Engine::UI
{
    GameObjectsMenu::GameObjectsMenu(UI::EditorManager *const editorManager)
        : GameObjectsMenu(editorManager, nullptr)
    {}

    GameObjectsMenu::GameObjectsMenu(UI::EditorManager *const editorManager, Objects::Scene *scene)
        : Menu("GameObjects", new GameObjectsMenuUI(this))
        , editorManager(editorManager)
        , scene(scene)
    {}

    GameObjectsMenu::~GameObjectsMenu()
    {}

    void GameObjectsMenu::Update()
    {
        UpdateUI();
    }

    size_t GameObjectsMenu::GetDefaultPriority() const
    {
        return priority;
    }

    bool GameObjectsMenu::IsActive() const
    {
        return Menu::IsActive() && scene;
    }

    void GameObjectsMenu::SetScene(Objects::Scene *value)
    {
        scene = value;
    }

    void GameObjectsMenu::SetTargetForEditor(Objects::GameObject *object)
    {
        editorManager->SetTarget(object);
        editorManager->SetActive(true);
    }
}