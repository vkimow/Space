#pragma once

#include "Engine/Graphics/PostProcessing/FrameBuffer.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTextureManager.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTextureRenderer.h"
#include "Engine/Graphics/PostProcessing/RenderBufferHandler.h"
#include "Engine/Graphics/PostProcessing/PostProcessingBufferHandler.h"
#include "Engine/Graphics/PostProcessing/PostProcessingSettings.h"
#include "Engine/Graphics/Elements/Container.h"

namespace Engine::Graphics
{
    class Bloom
    {
    public:
        Bloom(Container *container, FrameBufferTextureManager *textureManager, FrameBufferTextureRenderer *textureRenderer);
        ~Bloom();

    public:
        void Process(FrameBuffer &framebuffer, FrameBufferTexture *input, glm::ivec2 frame);
        FrameBufferTexture *const GetResult();

    private:
        Container *const container;
        FrameBufferTextureManager *const textureManager;
        FrameBufferTextureRenderer *const textureRenderer;
        PostProcessingBufferHandler brightnessThreshold;
        std::vector<PostProcessingBufferHandler> downsample;
        std::vector<PostProcessingBufferHandler> upsample;
    };
}