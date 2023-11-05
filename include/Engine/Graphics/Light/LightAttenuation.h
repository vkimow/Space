#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <initializer_list>
#include <string>

namespace Engine::Graphics
{
    class Shader;

    struct LightAttenuationUniform
    {
        LightAttenuationUniform();
        LightAttenuationUniform(Shader *shader, const std::string &path);
        GLuint k;
    };

    class LightAttenuation
    {
    public:
        LightAttenuation(float quadratic = 0.0075f, float linear = 0.045f, float constant = 1.0f);
        LightAttenuation(const glm::vec3& values);
        LightAttenuation(glm::vec3 &&values);
        LightAttenuation(std::initializer_list<float> values);
        LightAttenuation(const LightAttenuation &rhs);
        LightAttenuation(LightAttenuation &&rhs) noexcept;
        LightAttenuation &operator=(const LightAttenuation &rhs);
        LightAttenuation &operator=(LightAttenuation &&rhs) noexcept;
        ~LightAttenuation();

    public:
        bool operator==(const LightAttenuation &rhs);
        bool operator!=(const LightAttenuation &rhs);

    public:
        void Use(Shader *shader, const LightAttenuationUniform& uniform);

    public:
        void SetQuadratic(float value);
        void SetLinear(float value);
        void SetConstant(float value);

    public:
        float GetQuadratic() const;
        float GetLinear() const;
        float GetConstant() const;
        float &GetQuadratic();
        float &GetLinear();
        float &GetConstant();

    private:
        float quadratic;
        float linear;
        float constant;
    };
}