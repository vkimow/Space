#pragma once

#include <GL/glew.h>
#include "Engine/Tools/Events/MemberFunction.h"
#include <glm/glm.hpp>

namespace Engine
{
    class Window;
    class GraphicsModule;
}

namespace Engine::Graphics
{
    class Container;
    class FrameBufferTexture;
    class IFrameBufferHandler;
    class FrameBufferTextureRenderer
    {
    public:
        FrameBufferTextureRenderer();
        FrameBufferTextureRenderer(const FrameBufferTextureRenderer &rhs) = delete;
        FrameBufferTextureRenderer(FrameBufferTextureRenderer &&rhs) noexcept = delete;
        FrameBufferTextureRenderer &operator=(const FrameBufferTextureRenderer &rhs) = delete;
        FrameBufferTextureRenderer &operator=(FrameBufferTextureRenderer &&rhs) noexcept = delete;
        ~FrameBufferTextureRenderer();

    public:
        void Render(FrameBufferTexture *texture);
        void Render(FrameBufferTexture *textures, size_t count);
        void Render(const std::vector<FrameBufferTexture*>& textures);
        void Render(auto begin, auto end)
        {
            glBindVertexArray(rectVAO);
            size_t index = 0;
            for (auto it = begin; it != end && index < 16; ++it, ++index)
            {
                glActiveTexture(GL_TEXTURE0 + index);
                glBindTexture(GL_TEXTURE_2D, it->GetID());
            }
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }

    private:
        GLuint rectVAO;
        GLuint rectVBO;
    };
}