#pragma once 
#include <GL/glew.h>
#include "Engine/Graphics/Light/ILight.h"
#include "Engine/Graphics/Light/LightValue.h"
#include "Engine/Graphics/Light/LightSourceType.h"
#include "Engine/Graphics/Light/LightAttenuation.h"
#include "Engine/Objects/Transform.h"

namespace Engine::Objects
{
    class Script;
}

namespace Engine::Graphics
{
    class LightManager;
    class LightSourceUnfiromGetter;
    class Shader;

    class LightSource final: public ILight
    {
        friend class LightManager;
        friend class LightContainer;
        friend class Objects::Script;
        friend class LightSourceUnfiromGetter;

    protected:
        struct PointLightUniform
        {
            PointLightUniform();
            PointLightUniform(Shader *shader, const std::string &path);

            LightValueUniform ambient;
            LightValueUniform diffuse;
            LightValueUniform specular;
            LightAttenuationUniform attenuation;
            GLuint position;
            GLuint radius;
        };

        struct SpotLightUniform final: public PointLightUniform
        {
            SpotLightUniform();
            SpotLightUniform(Shader *shader, const std::string &path);

            GLuint direction;
            GLuint angle;
        };

    private:
        LightSource(LightManager *lightManager);
        ~LightSource();

    public:
        LightSource(const LightSource &rhs);
        LightSource(LightSource &&rhs) noexcept = delete;
        LightSource &operator=(const LightSource &rhs);
        LightSource &operator=(LightSource &&rhs) noexcept = delete;

    public:
        void Use(Shader *shader) override final;
        void Disable(Shader *shader) override final;

    public:
        void SetActive(bool value) override final;
        bool IsActive() const override final;

    public:
        void SetType(LightSourceType value);
        void SetTransform(Objects::Transform *value);
        void SetAngle(float value);
        void SetAngleInDegrees(float value);
        void SetRadius(float value);

    public:
        LightSourceType GetType() const;
        const glm::vec3 &GetPosition() const;
        const LightValue &GetAmbient() const;
        const LightValue &GetDiffuse() const;
        const LightValue &GetSpecular() const;
        const LightAttenuation &GetAttenuation() const;
        LightValue &GetAmbient();
        LightValue &GetDiffuse();
        LightValue &GetSpecular();
        LightAttenuation &GetAttenuation();
        const glm::vec3 &GetDirection() const;
        float GetAngle() const;
        float GetAngleInDegrees() const;
        float GetRadius();

    public:
        void ClearTransofrm();

    private:
        LightManager *const lightManager;

    private:
        bool isActive;
        LightSourceType type;
        Objects::Transform *transform;
        LightValue ambient;
        LightValue diffuse;
        LightValue specular;
        LightAttenuation attenuation;
        float radius;

    private:
        float angle;
        float halfAngleCos;
    };
}
