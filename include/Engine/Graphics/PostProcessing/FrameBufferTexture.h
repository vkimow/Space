#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Engine/Tools/Events/MemberFunction.h"
#include "Engine/Tools/Events/Action.h"

namespace Engine::Graphics
{
    class FrameBufferTextureManager;
    class FrameBufferTexture
    {
    public:
        FrameBufferTexture(FrameBufferTextureManager *textureManager);
        FrameBufferTexture(const FrameBufferTexture &rhs);
        FrameBufferTexture(FrameBufferTexture &&rhs) noexcept = delete;
        FrameBufferTexture &operator=(const FrameBufferTexture &rhs) = delete;
        FrameBufferTexture &operator=(FrameBufferTexture &&rhs) noexcept = delete;
        ~FrameBufferTexture();

    public:
        void Set(glm::ivec2 frame);
        GLuint GetID() const;

    private:
        FrameBufferTextureManager *textureManager;
        GLuint texture;
    };
}