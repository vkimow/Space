#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Main/Modules/GraphicsModule.h"
#include "Space/Scripts/CelestialBodyScript.h"
#include "Engine/Essentials/Scripts/Visuals/LightSourceScript.h"

namespace Main::Space
{
    class SpaceManager;

    class StarScript final: public Engine::Objects::Script
    {
    public:
        StarScript(Engine::Objects::GameObject *object, SpaceManager *space, Engine::GraphicsModule *graphics);
        StarScript(const StarScript &rhs);
        StarScript(StarScript &&rhs) noexcept;
        StarScript &operator=(const StarScript &rhs);
        StarScript &operator=(StarScript &&rhs) noexcept;
        ~StarScript();

    protected:
        Engine::Tools::Interfaces::IClonable *Clone() override final;
        void UpdateInner() override final;
        void UpdateEditor() override final;
        void SetGameObject(Engine::Objects::GameObject *value) override final;

    protected:
        void OnEnabledInner() override final;
        void OnDisabledInner() override final;

    public:
        size_t GetDefaultPriority() const override final;

    private:
        void SerializeScripts(Engine::Objects::GameObject* object);

    private:
        SpaceManager *const space;
        Engine::GraphicsModule *const graphics;
        CelestialBodyScript *celestialBodyScript;
        Engine::Scripts::LightSourceScript *lightSourceScript;

    private:
        const static size_t priority;
    };
}