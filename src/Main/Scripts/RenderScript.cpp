#include "Main/Scripts/RenderScript.h"

namespace Game::Scripts
{
    RenderScript::RenderScript()
    {}

    RenderScript::RenderScript(const RenderScript &rhs)
    {}

    RenderScript::RenderScript(RenderScript &&rhs) noexcept
    {}

    RenderScript &RenderScript::operator=(const RenderScript &rhs)
    {
        return *this;
    }

    RenderScript &RenderScript::operator=(RenderScript &&rhs) noexcept
    {
        return *this;
    }

    RenderScript::~RenderScript()
    {}

    Engine::Objects::Script *RenderScript::Clone() noexcept
    {
        return nullptr;
    }

    void RenderScript::UpdateInner()
    {}

    size_t RenderScript::GetDefaultPriority() const
    {
        return size_t();
    }
}