#pragma once

#include <type_traits>
#include <imgui.h>

namespace Engine::UI
{
    class Menu;

    class MenuUI
    {
        friend class Menu;

    protected:
        MenuUI(Menu *const menu, float width, float height, ImGuiWindowFlags_ flags = ImGuiWindowFlags_NoResize);
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
        ImVec2 size;
        ImGuiWindowFlags_ flags;
    };
}