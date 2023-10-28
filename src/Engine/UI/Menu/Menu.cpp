#include "Engine/UI/Menu/Menu.h"
#include "Engine/UI/Menu/MenuUI.h"

namespace Engine::UI
{
    Menu::Menu(const std::string &name, MenuUI *const ui)
        : name(name)
        , isActive(false)
        , ui(ui)
    {}

    Menu::~Menu()
    {
        delete ui;
    }

    void Menu::UpdateUI()
    {
        ui->Update();
    }

    void Menu::SetActive(bool value)
    {
        isActive = value;
    }

    bool Menu::IsActive() const
    {
        return isActive;
    }

    const std::string &Menu::GetName() const
    {
        return name;
    }
}