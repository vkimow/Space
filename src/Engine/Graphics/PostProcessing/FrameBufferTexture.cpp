#include "Engine/Graphics/PostProcessing/FrameBufferTexture.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTextureManager.h"
#include "Engine/Tools/Other/GL.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    FrameBufferTexture::FrameBufferTexture(FrameBufferTextureManager *textureManager)
        : textureManager(textureManager)
        , texture(0)
    {
        textureManager->AddTexture(this);
    }

    FrameBufferTexture::FrameBufferTexture(const FrameBufferTexture &rhs)
        : textureManager(rhs.textureManager)
        , texture(0)
    {
        textureManager->AddTexture(this);
    }

    FrameBufferTexture::~FrameBufferTexture()
    {
        textureManager->RemoveTexture(this);
        Engine::Tools::Graphics::ClearTexture(texture);
    }

    void FrameBufferTexture::Set(glm::ivec2 frame)
    {
        Tools::Graphics::ClearTexture(texture);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, frame.x, frame.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    GLuint FrameBufferTexture::GetID() const
    {
        return texture;
    }
}