#pragma once 
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace Engine::Graphics
{
    class Shader;

    struct LightValueUniform
    {
        LightValueUniform();
        LightValueUniform(Shader *shader, const std::string &path);
        GLuint colorWithIntensity;
    };

    class LightValue
    {
        friend class AmbientLight;
        friend class AmbientLight;
        friend class DirectionalLight;
        friend class LightSource;

    public:
        LightValue();
        LightValue(const glm::vec3 &color, float intensity);
        LightValue(glm::vec3 &&color, float intensity);
        LightValue(float r, float g, float b, float intensity);
        LightValue(const glm::vec4 &colorWithIntensity);
        LightValue(std::initializer_list<float> values);
        LightValue(const LightValue &rhs);
        LightValue(LightValue &&rhs) noexcept;
        LightValue &operator=(const LightValue &rhs);
        LightValue &operator=(LightValue &&rhs) noexcept;
        ~LightValue();

    public:
        bool operator==(const LightValue &rhs);
        bool operator!=(const LightValue &rhs);

    private:
        void Use(Shader *shader, const LightValueUniform &uniform);
        void Disable(Shader *shader, const LightValueUniform &uniform);

    public:
        void SetColor(const glm::vec3 &value);
        void SetColor(glm::vec3 &&value);
        void SetColor(float r, float g, float b);
        void SetIntensity(float value);

    public:
        glm::vec4 GetColorWithIntensity() const;
        const glm::vec3& GetColor() const;
        float GetIntensity() const;

    public:
        glm::vec3 &GetColor();
        float &GetIntensity();

    private:
        glm::vec3 color;
        float intensity;
    };
}
