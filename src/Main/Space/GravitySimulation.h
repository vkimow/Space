#pragma once

#include <unordered_map>
#include <unordered_set>
#include <glm/glm.hpp>

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
        GravitySimulation(SpaceManager *space);
        GravitySimulation(const GravitySimulation &rhs) = delete;
        GravitySimulation(GravitySimulation &&rhs) = delete;
        GravitySimulation &operator=(const GravitySimulation &rhs) = delete;
        GravitySimulation &operator=(GravitySimulation &&rhs) = delete;
        ~GravitySimulation();

    private:
        void Update();
        void CalculatePaths();

    public:
        const std::vector<glm::vec3> &GetPath(CelestialBodyScript * const script);

    private:
        SpaceManager *const space;
        CelestialBodiesPaths paths;
        CelestialBodiesPathsUsage pathsUsage;
    };
}