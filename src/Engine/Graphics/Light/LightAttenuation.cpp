#include "Engine/Graphics/Light/LightAttenuation.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Graphics/Elements/Shader.h"

namespace Engine::Graphics
{
    LightAttenuationUniform::LightAttenuationUniform()
        : k(0)
    {}

    LightAttenuationUniform::LightAttenuationUniform(Shader *shader, const std::string &path)
        : k(shader->GetUniform(path, false))
    {}

    LightAttenuation::LightAttenuation(float quadratic, float linear, float constant)
        : quadratic(quadratic)
        , linear(linear)
        , constant(constant)
    {}
    LightAttenuation::LightAttenuation(const glm::vec3 & values)
        : quadratic(values.x)
        , linear(values.y)
        , constant(values.z)
    {}
    LightAttenuation::LightAttenuation(glm::vec3 &&values)
        : quadratic(std::move(values.x))
        , linear(std::move(values.y))
        , constant(std::move(values.z))
    {}
    LightAttenuation::LightAttenuation(const LightAttenuation & rhs)
        : quadratic(rhs.quadratic)
        , linear(rhs.linear)
        , constant(rhs.constant)
    {}
    LightAttenuation::LightAttenuation(LightAttenuation && rhs) noexcept
        : quadratic(rhs.quadratic)
        , linear(rhs.linear)
        , constant(rhs.constant)
    {}

    LightAttenuation::LightAttenuation(std::initializer_list<float> values)
        : quadratic(0.0075f)
        , linear(0.045f)
        , constant(1.0f)
    {
        if (values.size() == 0 || values.size() > 3)
        {
            LOG_ERROR("Initializer list should include from 1 to 3 values");
        }

        auto it = values.begin();
        quadratic = *it;
        ++it;

        if (it == values.end()) return;
        linear = *it;
        ++it;

        if (it == values.end()) return;
        constant = *it;
    }

    LightAttenuation &LightAttenuation::operator=(const LightAttenuation & rhs)
    {
        quadratic = rhs.quadratic;
        linear = rhs.linear;
        constant = rhs.constant;
        return *this;
    }

    LightAttenuation &LightAttenuation::operator=(LightAttenuation &&rhs) noexcept
    {
        quadratic = rhs.quadratic;
        linear = rhs.linear;
        constant = rhs.constant;
        return *this;
    }

    LightAttenuation::~LightAttenuation()
    {}

    bool LightAttenuation::operator==(const LightAttenuation &rhs)
    {
        return quadratic == rhs.quadratic && linear == rhs.linear && constant == rhs.constant;
    }

    bool LightAttenuation::operator!=(const LightAttenuation &rhs)
    {
        return !operator==(rhs);
    }

    void LightAttenuation::Use(Shader * shader, const LightAttenuationUniform & uniform)
    {
        shader->SetVector3f(uniform.k, quadratic, linear, constant);
    }

    void LightAttenuation::SetQuadratic(float value)
    {
        quadratic = value;
    }
    void LightAttenuation::SetLinear(float value)
    {
        linear = value;
    }
    void LightAttenuation::SetConstant(float value)
    {
        constant = value;
    }

    float LightAttenuation::GetQuadratic() const
    {
        return quadratic;
    }
    float LightAttenuation::GetLinear() const
    {
        return linear;
    }
    float LightAttenuation::GetConstant() const
    {
        return constant;
    }

    float &LightAttenuation::GetQuadratic()
    {
        return quadratic;
    }
    float &LightAttenuation::GetLinear()
    {
        return linear;
    }
    float &LightAttenuation::GetConstant()
    {
        return constant;
    }
}