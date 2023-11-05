#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Main/Modules/GraphicsModule.h"

namespace Main::Space
{
    class SpaceManager;

    class CelestialBodyScript final: public Engine::Objects::Script
    {
    public:
        CelestialBodyScript(Engine::Objects::GameObject *object, SpaceManager *space, Engine::GraphicsModule *graphics);
        CelestialBodyScript(Engine::Objects::GameObject *object, float mass, const glm::vec3 &velocity, SpaceManager *space, Engine::GraphicsModule *graphics);
        CelestialBodyScript(const CelestialBodyScript &rhs);
        CelestialBodyScript(CelestialBodyScript &&rhs) noexcept;
        CelestialBodyScript &operator=(const CelestialBodyScript &rhs);
        CelestialBodyScript &operator=(CelestialBodyScript &&rhs) noexcept;
        ~CelestialBodyScript();

    protected:
        Engine::Tools::Interfaces::IClonable *Clone() override final;
        void UpdateInner() override final;
        void UpdateEditor() override final;

    public:
        size_t GetDefaultPriority() const override final;

    public:
        void ApplyAcceleration(const glm::vec3 &acceleration);

    public:
        void SetMass(float value);
        void SetVelocity(const glm::vec3 &value);

    public:
        float GetMass() const;
        const glm::vec3 &GetVelocity() const;

    private:
        float mass;
        glm::vec3 velocity;
        SpaceManager *const space;
        Engine::GraphicsModule *const graphics;

    private:
        const static size_t priority;
    };
}