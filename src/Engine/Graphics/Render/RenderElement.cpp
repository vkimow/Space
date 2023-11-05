#include "Engine/Graphics/Render/RenderElement.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    RenderElement::RenderElement()
        : index(0)
        , isExist(false)
    {}

    RenderElement::RenderElement(size_t index)
        : index(index)
        , isExist(true)
    {}

    RenderElement::RenderElement(const RenderElement &rhs)
        : index(rhs.index)
        , isExist(rhs.isExist)
    {}
    RenderElement::RenderElement(RenderElement &&rhs) noexcept
        : index(rhs.index)
        , isExist(rhs.isExist)
    {
        rhs.isExist = false;
    }

    RenderElement &RenderElement::operator=(const RenderElement &rhs)
    {
        index = rhs.index;
        isExist = rhs.isExist;
        return *this;
    }

    RenderElement &RenderElement::operator=(RenderElement &&rhs) noexcept
    {
        index = rhs.index;
        isExist = rhs.isExist;
        rhs.isExist = false;
        return *this;
    }

    RenderElement::~RenderElement()
    {
        index = 0;
        isExist = false;
    }

    RenderElement::operator bool() const
    {
        return isExist;
    }

    RenderElement::operator bool()
    {
        return isExist;
    }

    RenderElement::operator size_t() const
    {
        if (!isExist)
        {
            LOG_ERROR("InnerRenderElement doesn't contain valid index");
        }

        return index;
    }

    RenderElement::operator size_t()
    {
        if (!isExist)
        {
            LOG_ERROR("InnerRenderElement doesn't contain valid index");
        }

        return index;
    }
    size_t RenderElement::GetIndex() const
    {
        return index;
    }
    bool RenderElement::IsExist() const
    {
        return isExist;
    }
}