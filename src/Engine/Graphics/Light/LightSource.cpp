#include "Engine/Graphics/Light/LightSource.h"
#include "Engine/Graphics/Light/LightManager.h"
#include "Engine/Graphics/Elements/Shader.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    LightSource::PointLightUniform::PointLightUniform()
        : ambient()
        , diffuse()
        , specular()
        , attenuation()
        , position(0)
    {}

    LightSource::PointLightUniform::PointLightUniform(Shader *shader, const std::string &path)
        : ambient(shader, path + ".ambient")
        , diffuse(shader, path + ".diffuse")
        , specular(shader, path + ".specular")
        , attenuation(shader, path + ".k")
        , position(shader->GetUniform(path + ".position", false))
    {}

    LightSource::SpotLightUniform::SpotLightUniform()
        : PointLightUniform()
        , direction(0)
        , angle(0)
    {}

    LightSource::SpotLightUniform::SpotLightUniform(Shader *shader, const std::string &path)
        : PointLightUniform(shader, path + ".base")
        , direction(shader->GetUniform(path + ".direction", false))
        , angle(shader->GetUniform(path + ".angle", false))
    {}

    LightSource::LightSource(LightManager *lightManager)
        : lightManager(lightManager)
        , isActive(true)
        , type(LightSourceType::PointLight)
        , transform(nullptr)
        , ambient()
        , diffuse()
        , specular()
        , attenuation()
        , angle(1.0f)
        , halfAngleCos(glm::cos(angle / 2.0f))
    {}

    LightSource::LightSource(const LightSource &rhs)
        : lightManager(rhs.lightManager)
        , type(rhs.type)
        , isActive(rhs.isActive)
        , transform(rhs.transform)
        , ambient(rhs.ambient)
        , diffuse(rhs.diffuse)
        , specular(rhs.specular)
        , attenuation(rhs.attenuation)
        , angle(rhs.angle)
        , halfAngleCos(rhs.halfAngleCos)
    {}

    LightSource &LightSource::operator=(const LightSource &rhs)
    {
        isActive = rhs.isActive;
        type = rhs.type;
        transform = rhs.transform;
        ambient = rhs.ambient;
        diffuse = rhs.diffuse;
        specular = rhs.specular;
        attenuation = rhs.attenuation;
        angle = rhs.angle;
        halfAngleCos = rhs.halfAngleCos;
        return *this;
    }

    LightSource::~LightSource()
    {}

    void LightSource::Use(Shader *shader)
    {
        auto &uniformGetter = lightManager->shadersToLightSourceUniformGetter.at(shader);
        switch (type)
        {
            case LightSourceType::PointLight:
            {
                auto &pointLightUniform = uniformGetter.GetNextPointLight();
                ambient.Use(shader, pointLightUniform.ambient);
                diffuse.Use(shader, pointLightUniform.diffuse);
                specular.Use(shader, pointLightUniform.specular);
                attenuation.Use(shader, pointLightUniform.attenuation);
                shader->SetVector3f(pointLightUniform.position, GetPosition());
                break;
            }
            case LightSourceType::SpotLight:
            {
                auto &spotLightUniform = uniformGetter.GetNextSpotLight();
                ambient.Use(shader, spotLightUniform.ambient);
                diffuse.Use(shader, spotLightUniform.diffuse);
                specular.Use(shader, spotLightUniform.specular);
                attenuation.Use(shader, spotLightUniform.attenuation);
                shader->SetVector3f(spotLightUniform.position, GetPosition());
                shader->SetVector3f(spotLightUniform.direction, GetDirection());
                shader->SetFloat(spotLightUniform.angle, halfAngleCos);
                break;
            }
        }
    }

    void LightSource::Disable(Shader *shader)
    {
        auto &uniformGetter = lightManager->shadersToLightSourceUniformGetter.at(shader);
        switch (type)
        {
            case LightSourceType::PointLight:
            {
                auto &pointLightUniform = uniformGetter.GetNextPointLight();
                ambient.Disable(shader, pointLightUniform.ambient);
                diffuse.Disable(shader, pointLightUniform.diffuse);
                specular.Disable(shader, pointLightUniform.specular);
                break;
            }
            case LightSourceType::SpotLight:
            {
                auto &spotLightUniform = uniformGetter.GetNextSpotLight();
                ambient.Disable(shader, spotLightUniform.ambient);
                diffuse.Disable(shader, spotLightUniform.diffuse);
                specular.Disable(shader, spotLightUniform.specular);
                break;
            }
        }
    }

    void LightSource::SetActive(bool value)
    {
        isActive = value;
    }

    bool LightSource::IsActive() const
    {
        return isActive && transform;
    }

    void LightSource::SetType(LightSourceType value)
    {
        type = value;
    }

    void LightSource::SetTransform(Objects::Transform *value)
    {
        transform = value;
    }

    void LightSource::SetAngle(float value)
    {
        constexpr float fullCircle = glm::pi<float>() * 2;;
        if (value > fullCircle)
        {
            value = fmodf(value, fullCircle);
        }

        constexpr float oneDegree = glm::radians(1.0f);
        if (value < oneDegree)
        {
            LOG_ERROR("Angle can't be less than 1 degree");
            value = oneDegree;
        }

        angle = value;
        halfAngleCos = glm::cos(value / 2.0f);
    }

    void LightSource::SetAngleInDegrees(float value)
    {
        SetAngle(glm::radians(value));
    }

    void LightSource::ClearTransofrm()
    {
        transform = nullptr;
    }

    const glm::vec3 &LightSource::GetPosition() const
    {
        return transform->GetPosition();
    }

    const LightValue &LightSource::GetAmbient() const
    {
        return ambient;
    }

    const LightValue &LightSource::GetDiffuse() const
    {
        return diffuse;
    }

    const LightValue &LightSource::GetSpecular() const
    {
        return specular;
    }

    const LightAttenuation &LightSource::GetAttenuation() const
    {
        return attenuation;
    }

    LightValue &LightSource::GetAmbient()
    {
        return ambient;
    }

    LightValue &LightSource::GetDiffuse()
    {
        return diffuse;
    }

    LightValue &LightSource::GetSpecular()
    {
        return specular;
    }

    LightAttenuation &LightSource::GetAttenuation()
    {
        return attenuation;
    }

    const glm::vec3 &LightSource::GetDirection() const
    {
        return transform->GetForwardDirection();
    }

    float LightSource::GetAngle() const
    {
        return angle;
    }

    float LightSource::GetAngleInDegrees() const
    {
        return glm::degrees(GetAngle());
    }

    LightSourceType LightSource::GetType() const
    {
        return type;
    }
}
