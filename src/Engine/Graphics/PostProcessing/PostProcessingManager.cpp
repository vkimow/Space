#include "Engine/Graphics/PostProcessing/PostProcessingManager.h"
#include "Engine/Graphics/Elements/Shader.h"
#include "Engine/Window/Window.h"
#include "Engine/Graphics/Elements/Container.h"
#include "Engine/Graphics/PostProcessing/Configs/CMakeConfig.h"

namespace Engine::Graphics
{
    PostProcessingManager::PostProcessingManager(Window *window, Container *container)
        : window(window)
        , container(container)
        , framebuffer()
        , textureManager(window)
        , textureRenderer()
        , settings(container)
        , renderBuffer(&textureManager)
        , colorCorrectionBuffer(&textureManager)
        , bloom(container, &textureManager, &textureRenderer)
        , finalBuffer(&textureManager)
        , onResolutionChanged(this, &PostProcessingManager::OnResolutionChanged)
    {
        renderBuffer.SetOutputCount(1);
        renderBuffer.SetRenderBuffer(window->GetResolution());
        colorCorrectionBuffer.SetInput(&renderBuffer);
        colorCorrectionBuffer.SetOutputCount(1);
        finalBuffer.AddInput(&colorCorrectionBuffer);
        finalBuffer.AddInput(bloom.GetResult());
        finalBuffer.SetOutputCount(1);

        CreateShaderFromFile(container, "ColorCorrection", Configs::COLOR_CORRECTION_VERT_RELATIVE_PATH, Configs::COLOR_CORRECTION_FRAG_RELATIVE_PATH);
        CreateShaderFromFile(container, "Brightness", Configs::BRIGHTNESS_VERT_RELATIVE_PATH, Configs::BRIGHTNESS_FRAG_RELATIVE_PATH);
        CreateShaderFromFile(container, "Downsample", Configs::BLUR_DOWNSAMPLE_VERT_RELATIVE_PATH, Configs::BLUR_DOWNSAMPLE_FRAG_RELATIVE_PATH);
        auto upscale = CreateShaderFromFile(container, "Upsample", Configs::BLUR_UPSAMPLE_VERT_RELATIVE_PATH, Configs::BLUR_UPSAMPLE_FRAG_RELATIVE_PATH);
        upscale->Use();
        upscale->SetInt("source_to_upscale", 0);
        upscale->SetInt("source_to_combine_with", 1);
        upscale->Disable();

        auto postProcessing = CreateShaderFromFile(container, "PostProcessing", Configs::POSTPROCESSING_VERT_RELATIVE_PATH, Configs::POSTPROCESSING_FRAG_RELATIVE_PATH);
        postProcessing->Use();
        postProcessing->SetInt("origin", 0);
        postProcessing->SetInt("bloom", 1);
        postProcessing->Disable();

        window->AddListenerOnFramebufferResize(onResolutionChanged);
        settings.SetToDefault();
    }

    PostProcessingManager::~PostProcessingManager()
    {
        window->RemoveListenerOnFramebufferResize(onResolutionChanged);
    }

    PostProcessingSettings &PostProcessingManager::GetSettings()
    {
        return settings;
    }

    void PostProcessingManager::PostProcess()
    {

        colorCorrectionBuffer.Use(framebuffer);
        container->GetShader("ColorCorrection")->Use();
        textureRenderer.Render(colorCorrectionBuffer.GetInput());
        container->GetShader("ColorCorrection")->Disable();
        colorCorrectionBuffer.Disable(framebuffer);

        bloom.Process(framebuffer, colorCorrectionBuffer.GetOutput(0), window->GetResolution());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        container->GetShader("PostProcessing")->Use();
        textureRenderer.Render(finalBuffer.GetInput());
        container->GetShader("PostProcessing")->Disable();
    }

    void PostProcessingManager::EnableRenderBuffer()
    {
        renderBuffer.Use(framebuffer);
    }

    void PostProcessingManager::DisableRenderBuffer()
    {
        renderBuffer.Disable(framebuffer);
    }

    void PostProcessingManager::OnResolutionChanged(glm::ivec2 resolution)
    {
        textureManager.ResizeTextures(resolution);
        renderBuffer.SetRenderBuffer(resolution);
    }
}

