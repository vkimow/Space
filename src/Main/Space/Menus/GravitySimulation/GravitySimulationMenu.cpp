#include "Space/Menus/GravitySimulation/GravitySimulationMenu.h"
#include "Space/Menus/GravitySimulation/GravitySimulationMenuUI.h"

namespace Main::Space
{
    GravitySimulationMenu::GravitySimulationMenu(GravitySimulation *gravitySimulation)
        : Menu("GravitySimulation", new GravitySimulationMenuUI(this))
        , gravitySimulation(gravitySimulation)
    {}

    GravitySimulationMenu::~GravitySimulationMenu()
    {}

    void GravitySimulationMenu::Update()
    {
        UpdateUI();
    }

    size_t GravitySimulationMenu::GetDefaultPriority() const
    {
        return priority;
    }
}