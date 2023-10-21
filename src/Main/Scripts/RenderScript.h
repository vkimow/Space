#pragma once
#include "Engine/Objects/Script.h"
#include "Engine/Objects/GameObject.h"

namespace Game::Scripts
{
    class RenderScript final: public Engine::Objects::Script
    {
    public:
        RenderScript();
        RenderScript(const RenderScript &rhs);
        RenderScript(RenderScript &&rhs) noexcept;

        RenderScript &operator=(const RenderScript &rhs);
        RenderScript &operator=(RenderScript &&rhs) noexcept;

        ~RenderScript();

    protected:
        Engine::Objects::Script *Clone() noexcept override;

    protected:
        void UpdateInner() override;
        size_t GetDefaultPriority() const override;

    private:
        const static size_t priority;
    };
}