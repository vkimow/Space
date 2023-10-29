#pragma once

#include "Engine/Tools/Structs/TypeMapWithPriority.h"
#include "Engine/UI/Menu/Menu.h"

namespace Engine
{
    class UIModule;
}

namespace Engine::UI
{
    class MenuContainer
    {
        friend class MenuManager;

    private:
        MenuContainer();
        MenuContainer(const MenuContainer &rhs) = delete;
        MenuContainer(MenuContainer &&rhs) = delete;
        MenuContainer &operator=(const MenuContainer &rhs) = delete;
        MenuContainer &operator=(MenuContainer &&rhs) = delete;
        ~MenuContainer();

    public:
        template<typename M, typename... Args, typename = std::enable_if_t<std::is_base_of_v<Menu, M>>>
        M *const Create(Args&&... args)
        {
            M *menu = new M(std::forward<Args>(args)...);
            menus.Add(menu);
            return menu;
        }

        template<typename M, typename = std::enable_if_t<std::is_base_of_v<Menu, M>>>
        M *const Get()
        {
            return menus.Get<M>();
        }

        template<typename M, typename = std::enable_if_t<std::is_base_of_v<Menu, M>>>
        void Remove()
        {
            return menus.Remove<M>();
        }

    public:
        auto begin() { return menus.begin(); }
        auto end() { return menus.end(); }
        auto begin() const { return menus.begin(); }
        auto end() const { return menus.end(); }

    private:
        Tools::Structs::TypeMapWithPriority<Menu> menus;
    };
}