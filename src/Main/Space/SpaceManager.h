#pragma once
#include "Engine/Main/EngineHeader.h"
#include "Space/SpaceTime.h"
#include "Space/GameObjectManager.h"
#include "Space/Scripts/CelestialBodyScript.h"
#include "Space/GravitySimulation.h"

namespace Main::Space
{
    class SpaceManager
    {
        friend class SpaceMode;

    public:
        using CelestialBodyContainer = std::vector<CelestialBodyScript*>;

    private:
        SpaceManager(Engine::Graphics::Container* container);
        SpaceManager(const SpaceManager &rhs) = delete;
        SpaceManager(SpaceManager &&rhs) = delete;
        SpaceManager &operator=(const SpaceManager &rhs) = delete;
        SpaceManager &operator=(SpaceManager &&rhs) = delete;
        ~SpaceManager();

    private:
        void Update();

    public:
        SpaceTime& GetTime();
        const SpaceTime& GetTime() const;
        GravitySimulation &GetGravitySimulation();
        const GravitySimulation &GetGravitySimulation() const;
        CelestialBodyContainer &GetCelestialBodies();
        const CelestialBodyContainer &GetCelestialBodies() const;

    public:
        void AddCelestialBody(CelestialBodyScript* celestialBody);
        void RemoveCelestialBody(CelestialBodyScript* celestialBody);

    private:
        SpaceTime time;
        GravitySimulation gravitySimulation;
        CelestialBodyContainer celestialBodies;
    };
}