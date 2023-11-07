#include "Engine/Graphics/PostProcessing/FrameBuffer.h"
#include "Engine/Tools/Other/GL.h"
#include "Engine/Tools/Log/Logger.h"
#include <algorithm>
#include "Engine/Graphics/PostProcessing/FrameBufferTexture.h"


namespace Engine::Graphics
{
    FrameBuffer::FrameBuffer()
        : framebuffer(0)
    {
        glGenFramebuffers(1, &framebuffer);
    }

    FrameBuffer::~FrameBuffer()
    {
        Tools::Graphics::ClearFramebuffer(framebuffer);
    }

    void FrameBuffer::AttachRenderBuffer(GLuint rbo)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::AttachTextures(FrameBufferTexture *textures, size_t count)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        count = std::min(count, static_cast<size_t>(16));
        for (size_t i = 0; i < count; ++textures, ++i)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures->GetID(), 0);
        }

        auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG_ERROR("Framebuffer error: ", fboStatus);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::AttachTextures(const std::vector<FrameBufferTexture*>&textures)
    {
        AttachTextures(*textures.data(), textures.size());
    }


    void FrameBuffer::Use()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void FrameBuffer::Disable()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}