#pragma once

#include <vector>

namespace Engine::Graphics
{
    class FrameBuffer;
    class FrameBufferTexture;
    class IFrameBufferHandler
    {
    public:
        virtual void Use(FrameBuffer &framebuffer) = 0;
        virtual void Disable(FrameBuffer &framebuffer) = 0;

        virtual const std::vector<FrameBufferTexture *>& GetOutput() const =  0;
        virtual FrameBufferTexture * const GetOutput(size_t index) const = 0;
        virtual size_t GetOutputCount() const = 0;
    };
}