#pragma once

#include "Engine/UI/Menu/MenuUI.h"

namespace Main::Space
{
    class SpaceTimeMenu;

    class SpaceTimeMenuUI final: public Engine::UI::MenuUI
    {
        friend class SpaceTimeMenu;

    private:
        SpaceTimeMenuUI(SpaceTimeMenu *const menu);
        SpaceTimeMenuUI(const SpaceTimeMenuUI &rhs) = delete;
        SpaceTimeMenuUI(SpaceTimeMenuUI &&rhs) noexcept = delete;
        SpaceTimeMenuUI &operator=(const SpaceTimeMenuUI &rhs) = delete;
        SpaceTimeMenuUI &operator=(SpaceTimeMenuUI &&rhs) noexcept = delete;
        ~SpaceTimeMenuUI() = default;

    protected:
        void UpdateInner() override final;
    };
}