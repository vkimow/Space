#pragma once

#include "Engine/Graphics/PostProcessing/FrameBuffer.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTextureManager.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTextureRenderer.h"
#include "Engine/Graphics/PostProcessing/RenderBufferHandler.h"
#include "Engine/Graphics/PostProcessing/PostProcessingBufferHandler.h"
#include "Engine/Graphics/PostProcessing/PostProcessingSettings.h"
#include "Engine/Graphics/PostProcessing/Bloom/Bloom.h"

namespace Engine
{
    class Window;
    class GraphicsModule;
}

namespace Engine::Graphics
{
    class Container;

    class PostProcessingManager
    {
        friend class GraphicsModule;

    private:
        PostProcessingManager(Window *window, Container *container);
        PostProcessingManager(const PostProcessingManager &rhs) = delete;
        PostProcessingManager(PostProcessingManager &&rhs) noexcept = delete;
        PostProcessingManager &operator=(const PostProcessingManager &rhs) = delete;
        PostProcessingManager &operator=(PostProcessingManager &&rhs) noexcept = delete;
        ~PostProcessingManager();

    public:
        PostProcessingSettings &GetSettings();

    public:
        void PostProcess();
        void EnableRenderBuffer();
        void DisableRenderBuffer();

    private:
        void OnResolutionChanged(glm::ivec2 resolution);
        Tools::Events::MemberFunction<PostProcessingManager, glm::ivec2> onResolutionChanged;

    private:
        Window *const window;
        Container *const container;
        FrameBuffer framebuffer;
        FrameBufferTextureManager textureManager;
        FrameBufferTextureRenderer textureRenderer;
        PostProcessingSettings settings;

        RenderBufferHandler renderBuffer;

        PostProcessingBufferHandler colorCorrectionBuffer;

        Bloom bloom;

        PostProcessingBufferHandler finalBuffer;
    };
}