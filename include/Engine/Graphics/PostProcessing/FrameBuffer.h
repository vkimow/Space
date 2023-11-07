#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Engine/Tools/Events/MemberFunction.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    class FrameBufferTexture;
    class FrameBuffer
    {
        friend class PostProcessingManager;
    private:
        FrameBuffer();
        FrameBuffer(const FrameBuffer &rhs) = delete;
        FrameBuffer(FrameBuffer &&rhs) = delete;
        FrameBuffer &operator=(const FrameBuffer &rhs) = delete;
        FrameBuffer &operator=(FrameBuffer &&rhs) = delete;
        ~FrameBuffer();

    public:
        void AttachRenderBuffer(GLuint rbo);
        void AttachTextures(FrameBufferTexture *textures, size_t count);
        void AttachTextures(const std::vector<FrameBufferTexture *>& textures);
        void AttachTextures(auto begin, auto end)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
            size_t index = 0;
            for (auto it = begin; it != end && index < 16; ++it, ++index)
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, it->GetID(), 0);
            }

            auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
            {
                LOG_ERROR("Framebuffer error: ", fboStatus);
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Use();
        void Disable();

    private:
        GLuint framebuffer;
    };
}