#pragma once

#include <type_traits>

namespace Engine::UI
{
    class Menu;

    class MenuUI
    {
        friend class Menu;

    protected:
        MenuUI(Menu *const menu);
        MenuUI(const MenuUI &rhs) = delete;
        MenuUI(MenuUI &&rhs) noexcept = delete;
        MenuUI &operator=(const MenuUI &rhs) = delete;
        MenuUI &operator=(MenuUI &&rhs) noexcept = delete;
        virtual ~MenuUI();

    private:
        void Update();

    protected:
        virtual void UpdateInner() = 0;

    protected:
        template<typename M, typename = std::enable_if_t<std::is_base_of_v<Menu, M>>>
        M *const GetMenu() { return static_cast<M *const>(menu); }

    private:
        Menu *const menu;
    };
}