#include "Engine/Graphics/PostProcessing/FrameBufferTextureRenderer.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTexture.h"
#include "Engine/Graphics/PostProcessing/IFrameBufferHandler.h"
#include "Engine/Tools/Other/GL.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Window/Window.h"

namespace Engine::Graphics
{

    static float rectangleVertices[] =
    {
        // Coords    // texCoords
         1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f,

         1.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f
    };


    FrameBufferTextureRenderer::FrameBufferTextureRenderer()
        : rectVAO(0)
        , rectVBO(0)
    {
        glGenVertexArrays(1, &rectVAO);
        glGenBuffers(1, &rectVBO);
        glBindVertexArray(rectVAO);
        glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    }

    FrameBufferTextureRenderer::~FrameBufferTextureRenderer()
    {
        Tools::Graphics::ClearBuffer(rectVBO);
        Tools::Graphics::ClearVertexArray(rectVAO);
    }

    void FrameBufferTextureRenderer::Render(FrameBufferTexture *texture)
    {
        glBindVertexArray(rectVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetID());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void FrameBufferTextureRenderer::Render(FrameBufferTexture *textures, size_t count)
    {
        glBindVertexArray(rectVAO);
        count = std::min(count, static_cast<size_t>(16));
        for (size_t i = 0; i < count; ++i, ++textures)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textures->GetID());
        }
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void FrameBufferTextureRenderer::Render(const std::vector<FrameBufferTexture *> &textures)
    {
        glBindVertexArray(rectVAO);
        size_t count = std::min(textures.size(), static_cast<size_t>(16));
        for (size_t i = 0; i < count; ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textures[i]->GetID());
        }
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}