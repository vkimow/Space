#pragma once
#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuContainer.h"
#include "Engine/Objects/Scene.h"
#include "Engine/UI/Editor/EditorManager.h"

namespace Main::Editor
{
    class GameObjectManager;
}

namespace Main::Editor
{
    class GameObjectsMenu final: public Engine::UI::Menu
    {
        friend class Engine::UI::MenuContainer;
        friend class GameObjectsMenuUI;

    private:
        GameObjectsMenu(GameObjectManager *const objectsManager);
        GameObjectsMenu(const GameObjectsMenu &rhs) = delete;
        GameObjectsMenu(GameObjectsMenu &&rhs) noexcept = delete;
        GameObjectsMenu &operator=(const GameObjectsMenu &rhs) = delete;
        GameObjectsMenu &operator=(GameObjectsMenu &&rhs) noexcept = delete;
        ~GameObjectsMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;

    private:
        void SetTarget(Engine::Objects::GameObject *object);

    private:
        GameObjectManager *const objectsManager;

    private:
        static const size_t priority;
    };
}