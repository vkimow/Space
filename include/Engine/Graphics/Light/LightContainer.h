#pragma once 

#include "Engine/Graphics/Light/AmbientLight.h"
#include "Engine/Graphics/Light/DirectionalLight.h"
#include "Engine/Graphics/Light/LightSource.h"
#include "Engine/Tools/Events/EventsHeader.h"

namespace Engine::Scripts
{
    class LightSourceScript;
}

namespace Engine::Graphics
{
    class LightManager;

    class LightContainer final
    {
        friend class LightManager;
        friend class PointLight;
        friend class SpotLight;
        friend class Scripts::LightSourceScript;

    private:
        LightContainer(LightManager *lightManager);
        LightContainer(const LightContainer &rhs) = delete;
        LightContainer(LightContainer &&rhs) noexcept = delete;
        LightContainer &operator=(const LightContainer &rhs) = delete;
        LightContainer &operator=(LightContainer &&rhs) noexcept = delete;
        ~LightContainer();

    public:
        AmbientLight *InitializeAmbientLight();
        DirectionalLight *InitializeDirectionalLight();
        LightSource *CreateLightSource();

    private:
        void AddLightSource(LightSource *value);

    public:
        bool IsAmbientLightInitialized() const;
        bool IsDirectionalLightInitialized() const;

    public:
        AmbientLight *const GetAmbientLight() const;
        DirectionalLight *const GetDirectionalLight() const;
        const std::vector<LightSource *> &GetLightSources() const;

    public:
        void RemoveLightSource(LightSource *value);

    private:
        LightManager *lightManager;
        AmbientLight *ambient;
        DirectionalLight *directional;
        std::vector<LightSource *> lightSources;

    public:
        CREATE_ACTION(AmbientLight *, OnAmbientLightInitialized);
        CREATE_ACTION(DirectionalLight *, OnDirectionalLightInitialized);
        CREATE_ACTION(LightSource *, OnLightSourceCreated);
    };
}
