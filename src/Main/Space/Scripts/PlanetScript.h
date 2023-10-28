#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"

namespace Main::Space
{
    class PlanetScript final: public Engine::Objects::Script
    {
    public:
        PlanetScript();
        PlanetScript(const PlanetScript &rhs);
        PlanetScript(PlanetScript &&rhs) noexcept;
        PlanetScript &operator=(const PlanetScript &rhs);
        PlanetScript &operator=(PlanetScript &&rhs) noexcept;
        ~PlanetScript() = default;

    protected:
        Engine::Tools::Interfaces::IClonable *Clone() override final;

    protected:
        void UpdateInner() override final;
        size_t GetDefaultPriority() const override final;

    private:
        const static size_t priority;
    };
}