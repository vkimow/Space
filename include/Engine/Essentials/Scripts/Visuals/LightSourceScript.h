#pragma once

#include "Engine/Objects/Script.h"
#include "Engine/Graphics/Light/LightSourceType.h"

namespace Engine::Graphics
{
    class LightSource;
    class LightManager;
}

namespace Engine::Scripts
{
    class LightSourceScript final: public Objects::Script
    {
    public:
        LightSourceScript(Objects::GameObject *object, Graphics::LightManager *lightManager, Graphics::LightSourceType lightSourceType = Graphics::LightSourceType::PointLight);
        LightSourceScript(const LightSourceScript &rhs);
        LightSourceScript(LightSourceScript &&rhs) noexcept;
        LightSourceScript &operator=(const LightSourceScript &rhs);
        LightSourceScript &operator=(LightSourceScript &&rhs) noexcept;
        ~LightSourceScript();

    protected:
        Tools::Interfaces::IClonable *Clone() override final;
        void SetGameObject(Objects::GameObject *value) override final;
        void OnEnabledInner() override final;
        void OnDisabledInner() override final;

    protected:
        void UpdateInner() override final;

    protected:
        void UpdateEditor() override final;
        void SelectEditor() override final;
        void DeselectEditor() override final;

    public:
        void SetDefaultLightSource(Graphics::LightSourceType value);
        Graphics::LightSource *const GetLightSource() const;
        void ClearLightSource();

    public:
        size_t GetDefaultPriority() const override final;

    private:
        Graphics::LightManager *lightManager;
        Graphics::LightSource *lightSource;

    private:
        const static size_t priority;
    };
}