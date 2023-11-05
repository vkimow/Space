#include "Engine/Graphics/Light/DirectionalLight.h"
#include "Engine/Graphics/Elements/Shader.h"

namespace Engine::Graphics
{
    DirectionalLight::DirectionalLightUniform::DirectionalLightUniform()
        : diffuse()
        , specular()
        , direction(0)
    {}
    DirectionalLight::DirectionalLightUniform::DirectionalLightUniform(Shader *shader, const std::string &path)
        : diffuse(shader, path + ".diffuse")
        , specular(shader, path + ".specular")
        , direction(shader->GetUniform(path + ".direction", false))
    {}

    DirectionalLight::DirectionalLight()
        : isActive(true)
        , diffuse()
        , specular()
        , direction(0.0f, 0.0f, -1.0f)
        , uniforms()
    {}

    DirectionalLight::~DirectionalLight()
    {}

    void DirectionalLight::Use(Shader *shader)
    {
        auto &uniform = uniforms.at(shader);
        diffuse.Use(shader, uniform.diffuse);
        specular.Use(shader, uniform.specular);
        shader->SetVector3f(uniform.direction, direction);
    }

    void DirectionalLight::Disable(Shader *shader)
    {
        auto &uniform = uniforms.at(shader);
        diffuse.Disable(shader, uniform.diffuse);
        specular.Disable(shader, uniform.specular);
    }

    void DirectionalLight::SetActive(bool value)
    {
        isActive = value;
    }

    bool DirectionalLight::IsActive() const
    {
        return isActive;
    }

    void DirectionalLight::InitializeUniform(Shader *shader, const std::string &path)
    {
        uniforms.emplace(shader, DirectionalLightUniform(shader, path));
    }

    void DirectionalLight::SetDirection(const glm::vec3 & value)
    {
        direction = glm::normalize(value);
    }

    void DirectionalLight::SetDirection(glm::vec3 &&value)
    {
        direction = glm::normalize(std::move(value));
    }

    void DirectionalLight::SetDirection(float x, float y, float z)
    {
        direction = glm::normalize(glm::vec3(x, y, z));
    }

    const LightValue &DirectionalLight::GetDiffuse() const
    {
        return diffuse;
    }

    const LightValue &DirectionalLight::GetSpecular() const
    {
        return specular;
    }

    LightValue &DirectionalLight::GetDiffuse()
    {
        return diffuse;
    }

    LightValue &DirectionalLight::GetSpecular()
    {
        return specular;
    }

    const glm::vec3 &DirectionalLight::GetDirection() const
    {
        return direction;
    }
}
