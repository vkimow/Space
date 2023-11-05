#include "Engine/Graphics/Light/LightSourceUniformGetter.h"
#include <sstream>

namespace Engine::Graphics
{
    static std::string GetIndexedShaderPath(size_t index, const std::string &path)
    {
        std::ostringstream ss;
        ss << path << "[" << index << "]";
        return ss.str();
    };

    static size_t MAX_LIGHTS_COUNT = 16;

    LightSourceUnfiromGetter::LightSourceUnfiromGetter(Shader *shader, const std::string &pointLightsPath, const std::string &spotLightsPath)
        : pointLights()
        , spotLights()
        , pointLightsCounter(0)
        , spotLightsCounter(0)
    {
        pointLights.reserve(MAX_LIGHTS_COUNT);
        spotLights.reserve(MAX_LIGHTS_COUNT);

        for (size_t i = 0; i < MAX_LIGHTS_COUNT; ++i)
        {
            pointLights.emplace_back(shader, GetIndexedShaderPath(i, pointLightsPath));
        }

        for (size_t i = 0; i < MAX_LIGHTS_COUNT; ++i)
        {
            spotLights.emplace_back(shader, GetIndexedShaderPath(i, spotLightsPath));
        }
    }

    LightSourceUnfiromGetter::LightSourceUnfiromGetter(LightSourceUnfiromGetter &&rhs) noexcept
        : pointLights(std::move(rhs.pointLights))
        , spotLights(std::move(rhs.spotLights))
        , pointLightsCounter(0)
        , spotLightsCounter(0)
    {}

    LightSourceUnfiromGetter::~LightSourceUnfiromGetter()
    {}

    bool LightSourceUnfiromGetter::LightSourceTypeLigthsAreFull(LightSourceType value) const
    {
        switch (value)
        {
            case Engine::Graphics::LightSourceType::PointLight:
                return PointLightsAreFull();
            case Engine::Graphics::LightSourceType::SpotLight:
                return SpotLightsAreFull();
        }

        return true;
    }

    bool LightSourceUnfiromGetter::PointLightsAreFull() const
    {
        return pointLightsCounter >= pointLights.size();
    }

    bool LightSourceUnfiromGetter::SpotLightsAreFull() const
    {
        return spotLightsCounter >= spotLights.size();
    }

    LightSource::PointLightUniform &LightSourceUnfiromGetter::GetNextPointLight()
    {
        return pointLights[pointLightsCounter++];
    }

    LightSource::SpotLightUniform &LightSourceUnfiromGetter::GetNextSpotLight()
    {
        return spotLights[spotLightsCounter++];
    }

    void LightSourceUnfiromGetter::ClearCounters()
    {
        pointLightsCounter = 0;
        spotLightsCounter = 0;
    }
}