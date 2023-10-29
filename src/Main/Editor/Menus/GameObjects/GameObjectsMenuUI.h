#pragma once

#include "Engine/UI/Menu/MenuUI.h"

namespace Main::Editor
{
    class GameObjectsMenu;

    class GameObjectsMenuUI final: public Engine::UI::MenuUI
    {
        friend class GameObjectsMenu;

    private:
        GameObjectsMenuUI(GameObjectsMenu *const menu);
        GameObjectsMenuUI(const GameObjectsMenuUI &rhs) = delete;
        GameObjectsMenuUI(GameObjectsMenuUI &&rhs) noexcept = delete;
        GameObjectsMenuUI &operator=(const GameObjectsMenuUI &rhs) = delete;
        GameObjectsMenuUI &operator=(GameObjectsMenuUI &&rhs) noexcept = delete;
        ~GameObjectsMenuUI() = default;

    protected:
        void UpdateInner() override final;
    };
}