#pragma once
#include "Engine/Main/EngineHeader.h"
#include "Space/SpaceTime.h"

namespace Main::Space
{
    class SpaceTimeMenu final: public Engine::UI::Menu
    {
        friend class Engine::UI::MenuContainer;
        friend class SpaceTimeMenuUI;

    private:
        SpaceTimeMenu(SpaceTime *time);
        SpaceTimeMenu(const SpaceTimeMenu &rhs) = delete;
        SpaceTimeMenu(SpaceTimeMenu &&rhs) noexcept = delete;
        SpaceTimeMenu &operator=(const SpaceTimeMenu &rhs) = delete;
        SpaceTimeMenu &operator=(SpaceTimeMenu &&rhs) noexcept = delete;
        ~SpaceTimeMenu();

    public:
        void Update() override final;
        size_t GetDefaultPriority() const override final;

    private:
        float GetTimeCoef() const;
        void SetTimeCoef(float value);

    private:
        SpaceTime *const time;

    private:
        static const size_t priority;
    };
}