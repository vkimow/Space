#pragma once

#include "Engine/UI/Menu/MenuUI.h"

namespace Engine::UI
{
    class TimeMenu;

    class TimeMenuUI final: public UI::MenuUI
    {
        friend class TimeMenu;

    private:
        TimeMenuUI(TimeMenu *const menu);
        TimeMenuUI(const TimeMenuUI &rhs) = delete;
        TimeMenuUI(TimeMenuUI &&rhs) noexcept = delete;
        TimeMenuUI &operator=(const TimeMenuUI &rhs) = delete;
        TimeMenuUI &operator=(TimeMenuUI &&rhs) noexcept = delete;
        ~TimeMenuUI() = default;

    protected:
        void UpdateInner() override final;
    };
}