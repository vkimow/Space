#include "Engine/Graphics/Light/LightContainer.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    static const size_t LIGHTS_MAX_COUNT = 1024;

    LightContainer::LightContainer(LightManager *lightManager)
        : lightManager(lightManager)
        , ambient(nullptr)
        , directional(nullptr)
        , lightSources()
    {
        lightSources.reserve(LIGHTS_MAX_COUNT);
    }

    LightContainer::~LightContainer()
    {
        if (ambient)
        {
            delete ambient;
        }

        if (directional)
        {
            delete directional;
        }

        for (auto it = lightSources.begin(); it != lightSources.end(); ++it)
        {
            delete *it;
        }
    }

    AmbientLight *LightContainer::InitializeAmbientLight()
    {
        if (ambient)
        {
            LOG_ERROR("Ambient light already initialized");
            return ambient;
        }

        ambient = new AmbientLight();
        OnAmbientLightInitialized(ambient);
        return ambient;
    }

    DirectionalLight *LightContainer::InitializeDirectionalLight()
    {
        if (directional)
        {
            LOG_ERROR("Directional light already initialized");
            return directional;
        }

        directional = new DirectionalLight();
        OnDirectionalLightInitialized(directional);
        return directional;
    }

    LightSource *LightContainer::CreateLightSource()
    {
        LightSource *light = new LightSource(lightManager);
        lightSources.push_back(light);
        OnLightSourceCreated(light);
        return light;
    }

    void LightContainer::AddLightSource(LightSource *value)
    {
        lightSources.push_back(value);
        OnLightSourceCreated(value);
    }

    bool LightContainer::IsAmbientLightInitialized() const
    {
        return ambient;
    }

    bool LightContainer::IsDirectionalLightInitialized() const
    {
        return directional;
    }

    AmbientLight *const LightContainer::GetAmbientLight() const
    {
        return ambient;
    }

    DirectionalLight *const LightContainer::GetDirectionalLight() const
    {
        return directional;
    }

    const std::vector<LightSource *> &LightContainer::GetLightSources() const
    {
        return lightSources;
    }

    void LightContainer::RemoveLightSource(LightSource *value)
    {
        auto it = find(lightSources.begin(), lightSources.end(), value);
        lightSources.erase(it);
        delete value;
    }
}
