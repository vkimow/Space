#include "Engine/Graphics/Light/LightManager.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    static const std::string SHADER_LIGHTS_PATH = "lights";
    static const std::string SHADER_POINT_LIGHTS_PATH = SHADER_LIGHTS_PATH + ".pointLights";
    static const std::string SHADER_SPOT_LIGHTS_PATH = SHADER_LIGHTS_PATH + ".spotLights";
    static const std::string SHADER_POINT_LIGHTS_COUNT_PATH = SHADER_LIGHTS_PATH + ".pointLightsCount";
    static const std::string SHADER_SPOT_LIGHTS_COUNT_PATH = SHADER_LIGHTS_PATH + ".spotLightsCount";
    static const std::string SHADER_AMBIENT_LIGHT_PATH = SHADER_LIGHTS_PATH + ".ambient";
    static const std::string SHADER_DIRECTIONAL_LIGHT_PATH = SHADER_LIGHTS_PATH + ".directional";

    LightManager::LightManager()
        : container(this)
        , initializeAmbientLightUniforms(this, &LightManager::InitializeAmbientLightUniformsForShadersInUse)
        , initializeDirectionalLightUniforms(this, &LightManager::InitializeDirectionalLightUniformsForShadersInUse)
    {
        container.AddListenerOnAmbientLightInitialized(initializeAmbientLightUniforms);
        container.AddListenerOnDirectionalLightInitialized(initializeDirectionalLightUniforms);
    }

    LightManager::~LightManager()
    {
        container.RemoveListenerOnAmbientLightInitialized(initializeAmbientLightUniforms);
        container.RemoveListenerOnDirectionalLightInitialized(initializeDirectionalLightUniforms);
    }

    void LightManager::Use(Shader *shader)
    {
        if (!shadersInUse.contains(shader))
        {
            InitializeAmbientLightsUniforms(shader);
            InitializeDirectionalLightsUniforms(shader);
            InitializeLightSourcesUniforms(shader);
            shadersInUse.insert(shader);
        }

        if (container.IsAmbientLightInitialized())
        {
            auto ambientLight = container.GetAmbientLight();
            if (ambientLight->IsActive())
            {
                ambientLight->Use(shader);
            }
            else
            {
                ambientLight->Disable(shader);
            }
        }

        if (container.IsDirectionalLightInitialized())
        {
            auto directionalLight = container.GetDirectionalLight();
            if (directionalLight->IsActive())
            {
                directionalLight->Use(shader);
            }
            else
            {
                directionalLight->Disable(shader);
            }
        }

        const auto &lightSources = container.GetLightSources();
        auto &uniforms = shadersToLightSourceUniformGetter.at(shader);
        LightSource *light = nullptr;
        for (auto it = lightSources.begin(); it != lightSources.end(); ++it)
        {
            light = *it;
            if (!light->IsActive())
            {
                continue;
            }

            if (uniforms.LightSourceTypeLigthsAreFull(light->GetType()))
            {
                LOG_ERROR("Too much light sources. Skiping.");
                continue;
            }
            
            if (light->IsActive())
            {
                light->Use(shader);
            }
            else
            {
                light->Disable(shader);
            }
        }

        shader->SetUnsigned(SHADER_POINT_LIGHTS_COUNT_PATH, uniforms.pointLightsCounter);
        shader->SetUnsigned(SHADER_SPOT_LIGHTS_COUNT_PATH, uniforms.spotLightsCounter);
        uniforms.ClearCounters();
    }

    void LightManager::InitializeAmbientLightsUniforms(Shader *shader)
    {
        if (container.IsAmbientLightInitialized())
        {
            container.GetAmbientLight()->InitializeUniform(shader, SHADER_AMBIENT_LIGHT_PATH);
        }
    }

    void LightManager::InitializeDirectionalLightsUniforms(Shader * shader)
    {
        if (container.IsDirectionalLightInitialized())
        {
            container.GetDirectionalLight()->InitializeUniform(shader, SHADER_DIRECTIONAL_LIGHT_PATH);
        }
    }

    void LightManager::InitializeLightSourcesUniforms(Shader *shader)
    {
        shadersToLightSourceUniformGetter.emplace(shader, LightSourceUnfiromGetter(shader, SHADER_POINT_LIGHTS_PATH, SHADER_SPOT_LIGHTS_PATH));
    }

    const LightContainer &LightManager::GetContainer() const
    {
        return container;
    }

    LightContainer &LightManager::GetContainer()
    {
        return container;
    }

    void LightManager::InitializeAmbientLightUniformsForShadersInUse(AmbientLight *light)
    {
        light->InitializeUniforms(shadersInUse.begin(), shadersInUse.end(), SHADER_AMBIENT_LIGHT_PATH);
    }

    void LightManager::InitializeDirectionalLightUniformsForShadersInUse(DirectionalLight *light)
    {
        light->InitializeUniforms(shadersInUse.begin(), shadersInUse.end(), SHADER_DIRECTIONAL_LIGHT_PATH);
    }
}
