#include "Engine/Essentials/Editors/LightSource/LightSourceEditor.h"
#include "Engine/Essentials/Editors/LightSource/LightSourceEditorUI.h"
#include "Engine/Graphics/Light/LightSource.h"

namespace Engine::UI
{
    LightSourceEditor::LightSourceEditor()
        : Editor("LightSource", new LightSourceEditorUI(this))
    {}

    LightSourceEditor::~LightSourceEditor()
    {}

    size_t LightSourceEditor::GetDefaultPriority() const
    {
        return priority;
    }

    std::type_index LightSourceEditor::GetScriptType() const
    {
        return std::type_index(typeid(Scripts::LightSourceScript));
    }

    void LightSourceEditor::UpdateFromTarget()
    {
        auto script = BufferTargetScript<Scripts::LightSourceScript>();
        Graphics::LightSource *lightSource = script->GetLightSource();
        type = lightSource->GetType();
        ambient = lightSource->GetAmbient();
        diffuse = lightSource->GetDiffuse();
        specular = lightSource->GetSpecular();
        attenuation = lightSource->GetAttenuation();
        angle = lightSource->GetAngle();
    }

    void LightSourceEditor::UpdateFromUI()
    {
        Graphics::LightSource *lightSource = GetTargetScript<Scripts::LightSourceScript>()->GetLightSource();
        if (type.IsValueDiffersFromBuffer())
        {
            type.SetValueToBuffer();
            lightSource->SetType(type);
        }

        if (ambient.IsValueDiffersFromBuffer())
        {
            ambient.SetValueToBuffer();
            lightSource->GetAmbient() = ambient;
        }

        if (diffuse.IsValueDiffersFromBuffer())
        {
            diffuse.SetValueToBuffer();
            lightSource->GetDiffuse() = diffuse;
        }

        if (specular.IsValueDiffersFromBuffer())
        {
            specular.SetValueToBuffer();
            lightSource->GetSpecular() = specular;
        }

        if (attenuation.IsValueDiffersFromBuffer())
        {
            attenuation.SetValueToBuffer();
            lightSource->GetAttenuation() = attenuation;
        }

        if (angle.IsValueDiffersFromBuffer())
        {
            angle.SetValueToBuffer();
            lightSource->SetAngle(angle);
        }
    }

    Buffer<Graphics::LightSourceType> &LightSourceEditor::GetType()
    {
        return type;
    }

    Buffer<Graphics::LightValue> &LightSourceEditor::GetAmbient()
    {
        return ambient;
    }

    Buffer<Graphics::LightValue> &LightSourceEditor::GetDiffuse()
    {
        return diffuse;
    }

    Buffer<Graphics::LightValue> &LightSourceEditor::GetSpecular()
    {
        return specular;
    }

    Buffer<Graphics::LightAttenuation> &LightSourceEditor::GetAttenuation()
    {
        return attenuation;
    }

    Buffer<float> &LightSourceEditor::GetAngle()
    {
        return angle;
    }
}