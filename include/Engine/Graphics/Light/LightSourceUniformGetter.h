#pragma once 
#include "Engine/Graphics/Light/LightSource.h"
#include <array>

namespace Engine::Objects
{
    class Script;
}

namespace Engine::Graphics
{
    class LightSourceUnfiromGetter
    {
        friend class LightManager;

    private:
        LightSourceUnfiromGetter(Shader *shader, const std::string &pointLightsPath, const std::string &spotLightsPath);
    public:
        LightSourceUnfiromGetter(const LightSourceUnfiromGetter &rhs) = delete;
        LightSourceUnfiromGetter(LightSourceUnfiromGetter &&rhs) noexcept;
        LightSourceUnfiromGetter &operator=(const LightSourceUnfiromGetter &rhs) = delete;
        LightSourceUnfiromGetter &operator=(LightSourceUnfiromGetter &&rhs) noexcept = delete;
        ~LightSourceUnfiromGetter();

    public:
        bool LightSourceTypeLigthsAreFull(LightSourceType value) const;
        bool PointLightsAreFull() const;
        bool SpotLightsAreFull() const;

    public:
        LightSource::PointLightUniform &GetNextPointLight();
        LightSource::SpotLightUniform &GetNextSpotLight();
        void ClearCounters();

    private:
        std::vector<LightSource::PointLightUniform> pointLights;
        std::vector<LightSource::SpotLightUniform> spotLights;
        size_t pointLightsCounter;
        size_t spotLightsCounter;
    };
}
