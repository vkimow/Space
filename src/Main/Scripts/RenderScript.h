#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Graphics/Render/RenderUnit.h"
#include "Engine/Graphics/Render/RenderManager.h"

namespace Game::Scripts
{
    class RenderScript final: public Engine::Objects::Script
    {
    public:
        RenderScript(Engine::Objects::GameObject *object, Engine::Graphics::RenderManager *const manager);
        RenderScript(const RenderScript &rhs);
        RenderScript(RenderScript &&rhs) noexcept;
        RenderScript &operator=(const RenderScript &rhs);
        RenderScript &operator=(RenderScript &&rhs) noexcept;
        ~RenderScript();

    public:
        void AddRenderUnit(const Engine::Graphics::RenderUnit &unit);
        void AddRenderUnit(Engine::Graphics::RenderUnit &&unit);
        template<typename... Args>
        void EmplaceRenderUnit(Args... args)
        {
            units.push_back(manager->GetUnitBuilder().Create(std::forward<Args>(args)..., GetGameObject()->GetTransformPtr()));
        }

    private:
        void UpdateUnitsTransform();

    private:
        std::vector<Engine::Graphics::RenderUnit> units;
        Engine::Graphics::RenderManager *const manager;

    protected:
        Engine::Objects::Script *Clone() noexcept override final;
        void SetGameObject(Engine::Objects::GameObject *value) override final;

    protected:
        void UpdateInner() override final;
        size_t GetDefaultPriority() const override final;

    private:
        const static size_t priority;
    };
}