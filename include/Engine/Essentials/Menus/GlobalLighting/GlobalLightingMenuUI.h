#pragma once

#include "Engine/UI/Menu/MenuUI.h"

namespace Engine::UI
{
    class GlobalLightingMenu;

    class GlobalLightingMenuUI final: public MenuUI
    {
        friend class GlobalLightingMenu;

    private:
        GlobalLightingMenuUI(GlobalLightingMenu *const menu);
        GlobalLightingMenuUI(const GlobalLightingMenuUI &rhs) = delete;
        GlobalLightingMenuUI(GlobalLightingMenuUI &&rhs) noexcept = delete;
        GlobalLightingMenuUI &operator=(const GlobalLightingMenuUI &rhs) = delete;
        GlobalLightingMenuUI &operator=(GlobalLightingMenuUI &&rhs) noexcept = delete;
        ~GlobalLightingMenuUI() = default;

    protected:
        void UpdateInner() override final;
    };
}