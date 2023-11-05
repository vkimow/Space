#include "Space/Menus/GravitySimulation/GravitySimulationMenuUI.h"
#include "Space/Menus/GravitySimulation/GravitySimulationMenu.h"
#include <imgui.h>

namespace Main::Space
{
    GravitySimulationMenuUI::GravitySimulationMenuUI(GravitySimulationMenu *const menu)
        : MenuUI(menu, 220.0f,80.0f)
    {}

    void GravitySimulationMenuUI::UpdateInner()
    {
    }
}