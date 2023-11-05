#pragma once

#include "Engine/UI/Menu/MenuUI.h"

namespace Main::Space
{
    class GravitySimulationMenu;

    class GravitySimulationMenuUI final: public Engine::UI::MenuUI
    {
        friend class GravitySimulationMenu;

    private:
        GravitySimulationMenuUI(GravitySimulationMenu *const menu);
        GravitySimulationMenuUI(const GravitySimulationMenuUI &rhs) = delete;
        GravitySimulationMenuUI(GravitySimulationMenuUI &&rhs) noexcept = delete;
        GravitySimulationMenuUI &operator=(const GravitySimulationMenuUI &rhs) = delete;
        GravitySimulationMenuUI &operator=(GravitySimulationMenuUI &&rhs) noexcept = delete;
        ~GravitySimulationMenuUI() = default;

    protected:
        void UpdateInner() override final;
    };
}