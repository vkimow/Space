#pragma once

#include <glm/glm.hpp>
#include "Space/Scripts/CelestialBodyScript.h"

namespace Main::Space
{
    class CelestialBodyScript;
    struct CelestialBodyMock
    {
        CelestialBodyMock(CelestialBodyScript *const script)
            : original(script)
            , position(script->GetTransform().GetPosition())
            , mass(script->GetMass())
            , velocity(script->GetVelocity())
        {}

        CelestialBodyScript *const original;
        glm::vec3 position;
        const float mass;
        glm::vec3 velocity;
    };
}