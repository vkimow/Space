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

        LOG_DEBUG("Delta Time = {}", Engine::TimeModule::GetDeltaTime());
        LOG_DEBUG("Global Time = {}", Engine::TimeModule::GetGlobalTime());
        LOG_DEBUG("Space Time Coef = {}", timeCoef);
        LOG_DEBUG("Space Delta Time = {}", deltaTime);
        LOG_DEBUG("Space Global Time = {}", globalTime);
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