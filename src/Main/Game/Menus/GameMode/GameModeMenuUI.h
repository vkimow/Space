#pragma once

#include "Engine/UI/Menu/MenuUI.h"

namespace Main::Game
{
    class GameModeMenu;

    class GameModeMenuUI final: public Engine::UI::MenuUI
    {
        friend class GameModeMenu;

    private:
        GameModeMenuUI(GameModeMenu *const menu);
        GameModeMenuUI(const GameModeMenuUI &rhs) = delete;
        GameModeMenuUI(GameModeMenuUI &&rhs) noexcept = delete;
        GameModeMenuUI &operator=(const GameModeMenuUI &rhs) = delete;
        GameModeMenuUI &operator=(GameModeMenuUI &&rhs) noexcept = delete;
        ~GameModeMenuUI() = default;

    protected:
        void UpdateInner() override final;
    };
}