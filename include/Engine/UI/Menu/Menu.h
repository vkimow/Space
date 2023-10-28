#pragma once

#include <type_traits>
#include <typeindex>
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"

namespace Engine::UI
{
    class MenuUI;

    class Menu
    {
        friend class MenuContainer;
        friend class MenuManager;
        friend class MenuUI;

    protected:
        Menu(const std::string &name, MenuUI *const ui);
        Menu(const Menu &rhs) = delete;
        Menu(Menu &&rhs) noexcept = delete;
        Menu &operator=(const Menu &rhs) = delete;
        Menu &operator=(Menu &&rhs) noexcept = delete;

    public:
        virtual ~Menu();

    protected:
        virtual void Update() = 0;
        void UpdateUI();

    public:
        void SetActive(bool value);
        virtual bool IsActive() const;

    public:
        const std::string &GetName() const;
        virtual size_t GetDefaultPriority() const = 0;

    protected:
        template<typename MUI = MenuUI, typename = std::enable_if_t<std::is_base_of_v<MenuUI, MUI>>>
        MUI *const GetUI() { return static_cast<MUI *const>(ui); }

    private:
        const std::string name;
        bool isActive;
        MenuUI *const ui;
    };
}