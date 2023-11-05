#include "Space/SpaceTime.h"
#include "Engine/Main/EngineHeader.h"

namespace Main::Space
{
    SpaceTime::SpaceTime()
        : timeCoef(1.0f)
        , deltaTime(0.0f)
        , globalTime(0.0f)
    {}

    SpaceTime::~SpaceTime()
    {}

    void SpaceTime::Update()
    {
        deltaTime = timeCoef * Engine::TimeModule::GetDeltaTime();
        globalTime += deltaTime;
    }

    void SpaceTime::SetTimeCoef(float value)
    {
        timeCoef = value;
    }

    float SpaceTime::GetTimeCoef() const
    {
        return timeCoef;
    }

    float SpaceTime::GetDeltaTime() const
    {
        return deltaTime;
    }

    float SpaceTime::GetGlobalTime() const
    {
        return globalTime;
    }
}