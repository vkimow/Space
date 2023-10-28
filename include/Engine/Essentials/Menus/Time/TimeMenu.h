#pragma once
#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuContainer.h"

namespace Engine::UI
{
    class TimeMenu final: public UI::Menu
    {
        friend class UI::MenuContainer;
        friend class TimeMenuUI;

    private:
        TimeMenu();
        TimeMenu(const TimeMenu &rhs) = delete;
        TimeMenu(TimeMenu &&rhs) noexcept = delete;
        TimeMenu &operator=(const TimeMenu &rhs) = delete;
        TimeMenu &operator=(TimeMenu &&rhs) noexcept = delete;
        ~TimeMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;

    private:
        static size_t priority;
    };
}