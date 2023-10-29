#include "Editor/Menus/GameObjects/GameObjectsMenu.h"
#include "Editor/Menus/GameObjects/GameObjectsMenuUI.h"
#include "Editor/GameObjectManager.h"

namespace Main::Editor
{
    GameObjectsMenu::GameObjectsMenu(GameObjectManager *const objectsManager)
        : Menu("GameObjects", new GameObjectsMenuUI(this))
        , objectsManager(objectsManager)
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

    void GameObjectsMenu::SetTarget(Engine::Objects::GameObject *object)
    {
        objectsManager->Select(object);
    }
}