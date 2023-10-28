#pragma once
#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuContainer.h"
#include "Engine/Objects/Scene.h"
#include "Engine/UI/Editor/EditorManager.h"

namespace Engine::UI
{
    class GameObjectsMenu final: public UI::Menu
    {
        friend class UI::MenuContainer;
        friend class GameObjectsMenuUI;

    private:
        GameObjectsMenu(UI::EditorManager *const editorManager);
        GameObjectsMenu(UI::EditorManager *const editorManager, Objects::Scene *scene);
        GameObjectsMenu(const GameObjectsMenu &rhs) = delete;
        GameObjectsMenu(GameObjectsMenu &&rhs) noexcept = delete;
        GameObjectsMenu &operator=(const GameObjectsMenu &rhs) = delete;
        GameObjectsMenu &operator=(GameObjectsMenu &&rhs) noexcept = delete;
        ~GameObjectsMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;
        bool IsActive() const override final;

    public:
        void SetScene(Objects::Scene *value);

    private:
        void SetTargetForEditor(Objects::GameObject *object);

    private:
        UI::EditorManager *const editorManager;
        Objects::Scene *scene;

    private:
        static size_t priority;
    };
}