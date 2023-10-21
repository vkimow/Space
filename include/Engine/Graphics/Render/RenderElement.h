#pragma once

#include <vector>
#include <memory>
#include "Engine/Objects/Transform.h"

namespace Engine::Graphics
{

    struct RenderElement
    {           
    public:
        RenderElement();
        RenderElement(size_t index);
        RenderElement(const RenderElement &rhs);
        RenderElement(RenderElement &&rhs) noexcept;
        RenderElement &operator=(const RenderElement &rhs);
        RenderElement &operator=(RenderElement &&rhs) noexcept;
        ~RenderElement();

        explicit operator bool() const;
        explicit operator bool();

        explicit operator size_t() const;
        explicit operator size_t();

    public:
        size_t GetIndex() const;
        bool IsExist() const;

    private:
        size_t index;
        bool isExist;
    };
}