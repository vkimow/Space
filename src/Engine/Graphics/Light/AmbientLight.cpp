#include "Engine/Graphics/Light/AmbientLight.h"

namespace Engine::Graphics
{
    AmbientLight::AmbientLightUniform::AmbientLightUniform()
        : light()
    {}

    AmbientLight::AmbientLightUniform::AmbientLightUniform(Shader *shader, const std::string &path)
        : light(shader, path + ".light")
    {}

    AmbientLight::AmbientLight()
        : isActive(true)
        , light()
        , uniforms()
    {}

    AmbientLight::~AmbientLight()
    {}

    void AmbientLight::Use(Shader *shader)
    {
        auto &uniform = uniforms.at(shader);
        light.Use(shader, uniform.light);
    }

    void AmbientLight::Disable(Shader *shader)
    {
        auto &uniform = uniforms.at(shader);
        light.Disable(shader, uniform.light);
    }

    void AmbientLight::SetActive(bool value)
    {
        isActive = value;
    }

    bool AmbientLight::IsActive() const
    {
        return isActive;
    }

    const LightValue &AmbientLight::GetLight() const
    {
        return light;
    }

    LightValue &AmbientLight::GetLight()
    {
        return light;
    }

    void AmbientLight::InitializeUniform(Shader *shader, const std::string &path)
    {
        uniforms.emplace(shader, AmbientLightUniform(shader, path));
    }
}