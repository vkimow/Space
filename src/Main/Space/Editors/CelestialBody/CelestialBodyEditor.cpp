#include "Space/Editors/CelestialBody/CelestialBodyEditor.h"
#include "Space/Editors/CelestialBody/CelestialBodyEditorUI.h"
#include "Space/Scripts/CelestialBodyScript.h"

namespace Main::Space
{
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

    void CelestialBodyEditor::UpdateFromTarget()
    {
        BufferTargetScript<CelestialBodyScript>();
        mass = GetTargetScript<CelestialBodyScript>()->GetMass();
        velocity = GetTargetScript<CelestialBodyScript>()->GetVelocity();
    }

    void CelestialBodyEditor::UpdateFromUI()
    {
        if (mass.IsValueDiffersFromBuffer())
        {
            mass.SetValueToBuffer();
            GetTargetScript<CelestialBodyScript>()->SetMass(mass);
        }   

        if (velocity.IsValueDiffersFromBuffer())
        {
            velocity.SetValueToBuffer();
            GetTargetScript<CelestialBodyScript>()->SetVelocity(velocity);
        }
    }
}