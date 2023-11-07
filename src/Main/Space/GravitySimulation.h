#pragma once

#include <unordered_map>
#include <unordered_set>
#include <glm/glm.hpp>
#include "Engine/Graphics/Elements/Container.h"

namespace Main::Space
{
    class SpaceManager;
    class CelestialBodyScript;
    class GravitySimulation
    {
        friend class SpaceManager;
        using CelestialBodiesPaths = std::unordered_map<CelestialBodyScript *, std::vector<glm::vec3>>;
        using CelestialBodiesPathsUsage = std::unordered_set<CelestialBodyScript *>;

    private:
        GravitySimulation(SpaceManager *space, Engine::Graphics::Container *container);
        GravitySimulation(const GravitySimulation &rhs) = delete;
        GravitySimulation(GravitySimulation &&rhs) = delete;
        GravitySimulation &operator=(const GravitySimulation &rhs) = delete;
        GravitySimulation &operator=(GravitySimulation &&rhs) = delete;
        ~GravitySimulation();

    private:
        void Update();
        void UpdateLightning();
        void CalculatePaths();
            
    public:
        const std::vector<glm::vec3> &GetPath(CelestialBodyScript *const script);

    private:
        SpaceManager *const space;
        Engine::Graphics::Container* const container;
        CelestialBodiesPaths paths;
        CelestialBodiesPathsUsage pathsUsage;
    };
}