#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"
#include "Engine/Graphics/Render/RenderUnit.h"
#include "Engine/Graphics/Render/RenderManager.h"

namespace Engine::Scripts
{
    class RenderScript final: public Objects::Script
    {
    public:
        RenderScript(Objects::GameObject *object, Graphics::RenderManager *const manager);
        RenderScript(const RenderScript &rhs);
        RenderScript(RenderScript &&rhs) noexcept;
        RenderScript &operator=(const RenderScript &rhs);
        RenderScript &operator=(RenderScript &&rhs) noexcept;
        ~RenderScript();

    public:
        void AddRenderUnit(const Graphics::RenderUnit &unit);
        void AddRenderUnit(Graphics::RenderUnit &&unit);
        template<typename... Args>
        void EmplaceRenderUnit(Args... args)
        {
            units.push_back(manager->GetUnitBuilder().Create(std::forward<Args>(args)..., GetGameObject()->GetTransformPtr()));
        }

    private:
        void UpdateUnitsTransform();

    private:
        std::vector<Graphics::RenderUnit> units;
        Graphics::RenderManager *const manager;

    protected:
        Tools::Interfaces::IClonable *Clone() override final;
        void SetGameObject(Objects::GameObject *value) override final;

    protected:
        void UpdateInner() override final;

    protected:
        void UpdateEditor() override final;
        void SelectEditor() override final;
        void DeselectEditor() override final;

    public:
        size_t GetDefaultPriority() const override final;

    private:
        const static size_t priority;
    };
}