#pragma once
#include "Engine/Main/EngineHeader.h"
#include "Space/GravitySimulation.h"

namespace Main::Space
{
    class GravitySimulationMenu final: public Engine::UI::Menu
    {
        friend class Engine::UI::MenuContainer;
        friend class GravitySimulationMenuUI;

    private:
        GravitySimulationMenu(GravitySimulation *gravitySimulation);
        GravitySimulationMenu(const GravitySimulationMenu &rhs) = delete;
        GravitySimulationMenu(GravitySimulationMenu &&rhs) noexcept = delete;
        GravitySimulationMenu &operator=(const GravitySimulationMenu &rhs) = delete;
        GravitySimulationMenu &operator=(GravitySimulationMenu &&rhs) noexcept = delete;
        ~GravitySimulationMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;

    public:


    private:
        GravitySimulation *const gravitySimulation;

    private:
        static const size_t priority;
    };
}