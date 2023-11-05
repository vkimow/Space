#include "Engine/Graphics/Light/LightValue.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Graphics/Elements/Shader.h"

namespace Engine::Graphics
{
    LightValueUniform::LightValueUniform()
        : colorWithIntensity(0)
    {}
    LightValueUniform::LightValueUniform(Shader *shader, const std::string &path)
        : colorWithIntensity(shader->GetUniform(path + ".colorWithIntensity", false))
    {}

    LightValue::LightValue()
        : color(1.0f)
        , intensity(1.0f)
    {}
    LightValue::LightValue(const glm::vec3 & color, float intensity)
        : color(color)
        , intensity(intensity)
    {}
    LightValue::LightValue(glm::vec3 && color, float intensity)
        : color(std::move(color))
        , intensity(intensity)
    {}
    LightValue::LightValue(float r, float g, float b, float intensity)
        : color(r, g, b)
        , intensity(intensity)
    {}
    LightValue::LightValue(const glm::vec4 & colorWithIntensity)
        : color(colorWithIntensity.r, colorWithIntensity.g, colorWithIntensity.b)
        , intensity(colorWithIntensity.a)
    {}
    LightValue::LightValue(std::initializer_list<float> values)
        : color(1.0f)
        , intensity(1.0f)
    {
        if (values.size() != 3 && values.size() != 4)
        {
            LOG_ERROR("Initializer list should include 3 (color) numbers or 4 (color + intensity)");
        }

        auto it = values.begin();
        color.r = *it;
        ++it;

        if (it != values.end()) return;
        color.g = *it;
        ++it;

        if (it != values.end()) return;
        color.b = *it;
        ++it;

        if (it != values.end()) return;
        intensity = *it;
    }
    LightValue::LightValue(const LightValue & rhs)
        : color(rhs.color)
        , intensity(rhs.intensity)
    {}
    LightValue::LightValue(LightValue && rhs) noexcept
        :  color(std::move(rhs.color))
        , intensity(rhs.intensity)
    {}

    LightValue &LightValue::operator=(const LightValue & rhs)
    {
        color = rhs.color;
        intensity = rhs.intensity;
        return *this;
    }
    LightValue &LightValue::operator=(LightValue &&rhs) noexcept
    {
        color = std::move(rhs.color);
        intensity = rhs.intensity;
        return *this;
    }

    LightValue::~LightValue()
    {}


    bool LightValue::operator==(const LightValue &rhs)
    {
        return color == rhs.color && intensity == rhs.intensity;
    }

    bool LightValue::operator!=(const LightValue & rhs)
    {
        return !operator==(rhs);
    }


    void LightValue::Use(Shader * shader, const LightValueUniform & uniform)
    {
        shader->SetVector4f(uniform.colorWithIntensity, color.r, color.g, color.b, intensity);
    }

    void LightValue::Disable(Shader * shader, const LightValueUniform & uniform)
    {
        shader->SetVector4f(uniform.colorWithIntensity, 0.0f, 0.0f, 0.0f, 0.0f);
    }

    void LightValue::SetColor(const glm::vec3 & value)
    {
        color = value;
    }

    void LightValue::SetColor(glm::vec3 && value)
    {
        color = std::move(value);
    }

    void LightValue::SetColor(float r, float g, float b)
    {
        color = glm::vec3(r, g, b);
    }

    void LightValue::SetIntensity(float value)
    {
        intensity = value;
    }

    glm::vec4 LightValue::GetColorWithIntensity() const
    {
        return glm::vec4(color, intensity);
    }

    const glm::vec3 &LightValue::GetColor() const
    {
        return color;
    }
    float LightValue::GetIntensity() const
    {
        return intensity;
    }
    glm::vec3 &LightValue::GetColor()
    {
        return color;
    }
    float &LightValue::GetIntensity()
    {
        return intensity;
    }
}

