#include "Engine/Graphics/PostProcessing/FrameBufferTextureManager.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTexture.h"
#include "Engine/Tools/Other/GL.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Window/Window.h"

namespace Engine::Graphics
{
    FrameBufferTextureManager::FrameBufferTextureManager(Window *window)
        : window(window)
        , textures()
    {}

    FrameBufferTextureManager::~FrameBufferTextureManager()
    {}

    void FrameBufferTextureManager::AddTexture(FrameBufferTexture *texture)
    {
        textures.push_back(texture);
        texture->Set(window->GetResolution());
    }

    void FrameBufferTextureManager::RemoveTexture(FrameBufferTexture *texture)
    {
        auto it = std::find(textures.begin(), textures.end(), texture);
        textures.erase(it);
    }

    void FrameBufferTextureManager::ResizeTextures(glm::ivec2 frame)
    {
        for (auto it = textures.begin(); it != textures.end(); ++it)
        {
            (*it)->Set(frame);
        }
    }
}