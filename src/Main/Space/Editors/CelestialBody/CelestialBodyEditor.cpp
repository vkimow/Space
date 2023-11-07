#include "Space/Editors/CelestialBody/CelestialBodyEditor.h"
#include "Space/Editors/CelestialBody/CelestialBodyEditorUI.h"
#include "Space/Scripts/CelestialBodyScript.h"

namespace Main::Space
{
    const std::unordered_set<std::type_index> CelestialBodyEditor::editorsToDisable = {
        std::type_index(typeid(Engine::Objects::Transform))
    };

    CelestialBodyEditor::CelestialBodyEditor()
        : Editor("Celestial Body", new CelestialBodyEditorUI(this))
        , mass(0.0f)
        , velocity(0.0f)
    {}

    CelestialBodyEditor::~CelestialBodyEditor()
    {}

    size_t CelestialBodyEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index CelestialBodyEditor::GetScriptType() const
    {
        return std::type_index(typeid(CelestialBodyScript));
    }

    const std::unordered_set<std::type_index> *const CelestialBodyEditor::EditorsToDisable() const
    {
        return &editorsToDisable;
    }

    void CelestialBodyEditor::UpdateFromTarget()
    {
        BufferTargetScript<CelestialBodyScript>();
        position = GetTarget()->GetTransform().GetPosition();
        mass = GetTargetScript<CelestialBodyScript>()->GetMass();
        radius = GetTargetScript<CelestialBodyScript>()->GetRadius();
        velocity = GetTargetScript<CelestialBodyScript>()->GetVelocity();
    }

    void CelestialBodyEditor::UpdateFromUI()
    {
        if (position.IsValueDiffersFromBuffer())
        {
            position.SetValueToBuffer();
            GetTarget()->GetTransform().SetPosition(position);
        }

        if (mass.IsValueDiffersFromBuffer())
        {
            mass.SetValueToBuffer();
            GetTargetScript<CelestialBodyScript>()->SetMass(mass);
        }

        if (radius.IsValueDiffersFromBuffer())
        {
            radius.SetValueToBuffer();
            GetTargetScript<CelestialBodyScript>()->SetRadius(radius);
        }

        if (velocity.IsValueDiffersFromBuffer())
        {
            velocity.SetValueToBuffer();
            GetTargetScript<CelestialBodyScript>()->SetVelocity(velocity);
        }
    }
}