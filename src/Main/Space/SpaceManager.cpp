#include "Space/SpaceManager.h"
#include "Space/Menus/MenusHeader.h"

namespace Main::Space
{
    SpaceManager::SpaceManager()
        : time()
        , gravitySimulation(this)
        , celestialBodies()
    {}

    SpaceManager::~SpaceManager()
    {}

    void SpaceManager::Update()
    {
        time.Update();
        gravitySimulation.Update();
    }

    SpaceTime& SpaceManager::GetTime()
    {
        return time;
    }

    const SpaceTime& SpaceManager::GetTime() const
    {
        return time;
    }

    GravitySimulation &SpaceManager::GetGravitySimulation()
    {
        return gravitySimulation;
    }

    const GravitySimulation &SpaceManager::GetGravitySimulation() const
    {
        return gravitySimulation;
    }

    SpaceManager::CelestialBodyContainer &SpaceManager::GetCelestialBodies()
    {
        return celestialBodies;
    }

    const SpaceManager::CelestialBodyContainer &SpaceManager::GetCelestialBodies() const
    {
        return celestialBodies;
    }

    void SpaceManager::AddCelestialBody(CelestialBodyScript *celestialBody)
    {
        celestialBodies.push_back(celestialBody);
    }

    void SpaceManager::RemoveCelestialBody(CelestialBodyScript *celestialBodyToRemove)
    {
        auto pos = std::find_if(celestialBodies.begin(), celestialBodies.end(),
            [celestialBodyToRemove](CelestialBodyScript *celestialBody) { return celestialBodyToRemove == celestialBody; });

        celestialBodies.erase(pos);
    }
}