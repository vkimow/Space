#include "Space/Scripts/PlanetScript.h"

namespace Main::Space
{
    PlanetScript::PlanetScript()
    {}

    PlanetScript::PlanetScript(const PlanetScript & rhs)
    {}

    PlanetScript::PlanetScript(PlanetScript && rhs) noexcept
    {}

    PlanetScript &PlanetScript::operator=(const PlanetScript & rhs)
    {
        return *this;
    }

    PlanetScript &PlanetScript::operator=(PlanetScript &&rhs) noexcept
    {
        return *this;
    }

    Engine::Tools::Interfaces::IClonable *PlanetScript::Clone()
    {
        return new PlanetScript(*this);
    }

    void PlanetScript::UpdateInner()
    {}

    size_t PlanetScript::GetDefaultPriority() const
    {
        return priority;
    }
}