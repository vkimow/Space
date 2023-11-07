#include "Engine/Graphics/PostProcessing/RenderBufferHandler.h"
#include "Engine/Tools/Other/GL.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Graphics/PostProcessing/FrameBuffer.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTexture.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTextureManager.h"

namespace Engine::Graphics
{

    RenderBufferHandler::RenderBufferHandler(FrameBufferTextureManager *textureManager)
        : textureManager(textureManager)
        , outputTextures()
        , rbo()
    {}

    RenderBufferHandler::~RenderBufferHandler()
    {
        for (auto it = outputTextures.begin(); it != outputTextures.end(); ++it)
        {
            delete *it;
        }
        outputTextures.clear();
    }

    void RenderBufferHandler::SetRenderBuffer(glm::ivec2 frame)
    {
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, frame.x, frame.y);
    }

    void RenderBufferHandler::Use(FrameBuffer &framebuffer)
    {
        framebuffer.AttachRenderBuffer(rbo);
        framebuffer.AttachTextures(outputTextures);
        framebuffer.Use();
    }

    void RenderBufferHandler::Disable(FrameBuffer &framebuffer)
    {
        framebuffer.Disable();
    }

    void RenderBufferHandler::SetOutputCount(size_t value)
    {
        if (value > outputTextures.size())
        {
            for (size_t i = outputTextures.size(); i < value; ++i)
            {
                outputTextures.push_back(new FrameBufferTexture(textureManager));
            }
        }
        else
        {
            for (auto it = outputTextures.begin() + value; it != outputTextures.end(); ++it)
            {
                delete *it;
            }
            outputTextures.erase(outputTextures.begin() + value, outputTextures.end());
        }
    }

    const std::vector<FrameBufferTexture *> &RenderBufferHandler::GetOutput() const
    {
        return outputTextures;
    }

    FrameBufferTexture *const RenderBufferHandler::GetOutput(size_t index) const
    {
        return outputTextures[index];
    }

    size_t RenderBufferHandler::GetOutputCount() const
    {
        return size_t();
    }
}