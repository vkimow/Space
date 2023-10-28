#pragma once

#include "Engine/Tools/Structs/IndividualTypeContainerWithPriority.h"
#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuContainer.h"

namespace Engine
{
    class UIModule;
}

namespace Engine::UI
{
    class EditorManager;
    class MenuManager
    {
        friend class UIModule;

    private:
        MenuManager(EditorManager *editorManager);
        MenuManager(const MenuManager &rhs) = delete;
        MenuManager(MenuManager &&rhs) = delete;
        MenuManager &operator=(const MenuManager &rhs) = delete;
        MenuManager &operator=(MenuManager &&rhs) = delete;
        ~MenuManager();

    public:
        void Update();

    public:
        MenuContainer &GetContainer();

    private:
        MenuContainer container;
    };
}