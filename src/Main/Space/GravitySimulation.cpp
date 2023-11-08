#include "Space/GravitySimulation.h"
#include "Space/SpaceManager.h"
#include "Engine/Tools/Other/Geometry.h"
#include "Space/CelestialBodyMock.h"
#include "Space/Scripts/CelestialBodyScript.h"
#include <glm/gtc/type_ptr.hpp>
#include "Space/Scripts/StarScript.h"

namespace Main::Space
{
    static float GravitationalConstant = 0.0001f;

    static inline glm::vec3 CalculateAcceleration(const glm::vec3 &targetPos, const glm::vec3 &otherPos, float otherMass)
    {
        glm::vec3 dir = otherPos - targetPos;
        float sqrDistance = Engine::Tools::Geometry::GetSqrLength(dir);
        dir = Engine::Tools::Geometry::GetNormilizedFromSqrLength(dir, sqrDistance);
        return (dir * GravitationalConstant * otherMass) / sqrDistance;
    }

    static glm::vec3 CalculateAcceleration(CelestialBodyScript *target, auto bodiesStart, auto bodiesEnd)
    {
        glm::vec3 acceleration(0.0f);
        CelestialBodyScript *body = nullptr;
        for (auto it = bodiesStart; it != bodiesEnd; ++it)
        {
            body = *it;
            if (target == body)
            {
                continue;
            }

            acceleration += CalculateAcceleration(target->GetTransform().GetPosition(), body->GetTransform().GetPosition(), body->GetMass());
        }

        return acceleration;
    }

    static glm::vec3 CalculateAcceleration(const CelestialBodyMock &target, auto bodiesStart, auto bodiesEnd)
    {
        glm::vec3 acceleration(0.0f);
        for (auto it = bodiesStart; it != bodiesEnd; ++it)
        {
            if (target.original == it->original)
            {
                continue;
            }

            acceleration += CalculateAcceleration(target.position, it->position, it->mass);
        }

        return acceleration;
    }

    static glm::vec3 CalculateAcceleration(auto target, auto bodies)
    {
        return CalculateAcceleration(target, bodies.begin(), bodies.end());
    }

    static std::vector<CelestialBodyMock> GetMocks(auto bodiesStart, auto bodiesEnd)
    {
        std::vector<CelestialBodyMock> mocks;
        for (auto it = bodiesStart; it != bodiesEnd; ++it)
        {
            mocks.push_back(CelestialBodyMock(*it));
        }

        return mocks;
    }

    static std::vector<CelestialBodyMock> GetMocks(auto bodies)
    {
        return GetMocks(bodies.begin(), bodies.end());
    }

    GravitySimulation::GravitySimulation(SpaceManager *space, Engine::Graphics::Container *container)
        : space(space)
        , container(container)
        , paths()
        , pathsUsage()
    {}

    GravitySimulation::~GravitySimulation()
    {}

    void GravitySimulation::Update()
    {
        auto &celestialBodies = space->GetCelestialBodies();
        CelestialBodyScript *celestialBody = nullptr;
        for (auto it = celestialBodies.begin(); it != celestialBodies.end(); ++it)
        {
            celestialBody = *it;
            glm::vec3 acceleration = CalculateAcceleration(celestialBody, celestialBodies.begin(), celestialBodies.end());
            celestialBody->ApplyAcceleration(acceleration);
        }

        //UpdateLightning();
    }

    void GravitySimulation::UpdateLightning()
    {
        auto &celestialBodies = space->GetCelestialBodies();
        CelestialBodyScript *celestialBody = nullptr;
        std::vector<glm::vec4> positionAndRadius;
        std::vector<bool> useToCalculateLight;
        for (auto it = celestialBodies.begin(); it != celestialBodies.end(); ++it)
        {
            celestialBody = *it;
            positionAndRadius.emplace_back(celestialBody->GetTransform().GetPosition(), celestialBody->GetRadius());
            useToCalculateLight.push_back(!celestialBody->GetGameObject()->ConstainsScript<StarScript>());
        }

        size_t planetsCount = positionAndRadius.size() > 128 ? 128 : positionAndRadius.size();
        auto shader = container->GetShader("MainShader");
        shader->Use();
        for (size_t i = 0; i < planetsCount; ++i)
        {
            std::string planet = "space.planets[" + std::to_string(i) + "].positionAndRadius";
            shader->SetVector4f(planet, positionAndRadius[i]);
            std::string useToCalcLight = "space.planets[" + std::to_string(i) + "].useToCalculateLight";
            shader->SetInt(useToCalcLight, useToCalculateLight[i]);
        }
        shader->SetUnsigned("space.planetsCount", planetsCount);
        shader->Disable();
    }

    void GravitySimulation::CalculatePaths()
    {
        std::vector<CelestialBodyMock> mocks = GetMocks(space->GetCelestialBodies());
        size_t steps = 300;
        paths.clear();

        for (auto it = mocks.begin(); it != mocks.end(); ++it)
        {
            paths.emplace(it->original, std::vector<glm::vec3>(1000));
            paths[it->original][0] = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        const float timeStep = 10.f;
        for (size_t step = 1; step < steps; ++step)
        {
            for (auto it = mocks.begin(); it != mocks.end(); ++it)
            {
                glm::vec3 acceleration = CalculateAcceleration(*it, mocks);
                it->velocity += acceleration * timeStep;
            }

            for (auto it = mocks.begin(); it != mocks.end(); ++it)
            {      
                glm::vec3 positionDelta = it->velocity * timeStep;
                paths[it->original][step] = paths[it->original][step - 1] + positionDelta;
                it->position += positionDelta;
            }
        }
    }

    const std::vector<glm::vec3> &GravitySimulation::GetPath(CelestialBodyScript *const script)
    {
        if (pathsUsage.contains(script))
        {
            pathsUsage.clear();
        }

        if (pathsUsage.empty())
        {
            CalculatePaths();
            //UpdateLightning();
        }

        pathsUsage.insert(script);
        return paths.at(script);
    }
}