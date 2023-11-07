#pragma once

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
    class FrameBufferTextureManager
    {
    public:
        FrameBufferTextureManager(Window *window);
        FrameBufferTextureManager(const FrameBufferTextureManager &rhs) = delete;
        FrameBufferTextureManager(FrameBufferTextureManager &&rhs) noexcept = delete;
        FrameBufferTextureManager &operator=(const FrameBufferTextureManager &rhs) = delete;
        FrameBufferTextureManager &operator=(FrameBufferTextureManager &&rhs) noexcept = delete;
        ~FrameBufferTextureManager();

    public:
        void AddTexture(FrameBufferTexture *texture);
        void RemoveTexture(FrameBufferTexture *texture);

    public:
        void ResizeTextures(glm::ivec2 frame);

    private:
        Window *const window;
        std::vector<FrameBufferTexture *> textures;
    };
}