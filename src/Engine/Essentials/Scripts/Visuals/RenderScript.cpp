#include "Engine/Essentials/Scripts/Visuals/RenderScript.h"

namespace Engine::Scripts
{
    RenderScript::RenderScript(Objects::GameObject *object, Graphics::RenderManager *const manager)
        : Script(object)
        , manager(manager)
        , units()
    {}

    RenderScript::RenderScript(const RenderScript &rhs)
        : Script(rhs)
        , manager(rhs.manager)
        , units(rhs.units)
    {}

    RenderScript::RenderScript(RenderScript &&rhs) noexcept
        : Script(std::move(rhs))
        , manager(rhs.manager)
        , units(std::move(rhs.units))
    {}

    RenderScript &RenderScript::operator=(const RenderScript &rhs)
    {
        Script::operator=(rhs);
        units = rhs.units;
        return *this;
    }

    RenderScript &RenderScript::operator=(RenderScript &&rhs) noexcept
    {
        Script::operator=(std::move(rhs));
        units = std::move(rhs.units);
        return *this;
    }

    RenderScript::~RenderScript()
    {}

    Tools::Interfaces::IClonable *RenderScript::Clone()
    {
        return new RenderScript(*this);
    }

    void RenderScript::UpdateInner()
    {
        manager->GetPool().AddRenderUnit(units.begin(), units.end());
    }

    size_t RenderScript::GetDefaultPriority() const
    {
        return priority;
    }

    void RenderScript::SetGameObject(Objects::GameObject *value)
    {
        Script::SetGameObject(value);
        UpdateUnitsTransform();
    }

    void RenderScript::AddRenderUnit(const Graphics::RenderUnit &unit)
    {
        auto unitCopy = unit;
        unitCopy.SetTransform(GetGameObject()->GetTransformPtr());
        units.push_back(std::move(unitCopy));
    }

    void RenderScript::AddRenderUnit(Graphics::RenderUnit && unit)
    {
        unit.SetTransform(GetGameObject()->GetTransformPtr());
        units.push_back(std::move(unit));
    }

    void RenderScript::UpdateUnitsTransform()
    {
        for (auto it = units.begin(); it != units.end(); ++it)
        {
            it->SetTransform(GetGameObject()->GetTransformPtr());
        }
    }
}