#include "Engine/Graphics/PostProcessing/Bloom/Bloom.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTexture.h"

namespace Engine::Graphics
{
    Bloom::Bloom(Container *container, FrameBufferTextureManager *textureManager, FrameBufferTextureRenderer *textureRenderer)
        : container(container)
        , textureManager(textureManager)
        , textureRenderer(textureRenderer)
        , brightnessThreshold(textureManager)
        , downsample()
        , upsample()
    {
        downsample.emplace_back(textureManager);
        downsample.emplace_back(textureManager);
        downsample.emplace_back(textureManager);
        downsample.emplace_back(textureManager);
        downsample.emplace_back(textureManager);
        downsample.emplace_back(textureManager);
        upsample.emplace_back(textureManager);
        upsample.emplace_back(textureManager);
        upsample.emplace_back(textureManager);
        upsample.emplace_back(textureManager);
        upsample.emplace_back(textureManager);

        brightnessThreshold.SetOutputCount(1);
        downsample[0].SetInput(brightnessThreshold.GetOutput());
        downsample[0].SetOutputCount(1);
        downsample[1].SetInput(downsample[0].GetOutput());
        downsample[1].SetOutputCount(1);
        downsample[2].SetInput(downsample[1].GetOutput());
        downsample[2].SetOutputCount(1);
        downsample[3].SetInput(downsample[2].GetOutput());
        downsample[3].SetOutputCount(1);
        downsample[4].SetInput(downsample[3].GetOutput());
        downsample[4].SetOutputCount(1);
        downsample[5].SetInput(downsample[4].GetOutput());
        downsample[5].SetOutputCount(1);
        upsample[4].SetInput(downsample[5].GetOutput());
        upsample[4].AddInput(downsample[4].GetOutput());
        upsample[4].SetOutputCount(1);
        upsample[3].SetInput(upsample[4].GetOutput());
        upsample[3].AddInput(downsample[3].GetOutput());
        upsample[3].SetOutputCount(1);
        upsample[2].SetInput(upsample[3].GetOutput());
        upsample[2].AddInput(downsample[2].GetOutput());
        upsample[2].SetOutputCount(1);
        upsample[1].SetInput(upsample[2].GetOutput());
        upsample[1].AddInput(downsample[1].GetOutput());
        upsample[1].SetOutputCount(1);
        upsample[0].SetInput(upsample[1].GetOutput());
        upsample[0].AddInput(downsample[0].GetOutput());
        upsample[0].SetOutputCount(1);
    }

    Bloom::~Bloom()
    {}

    void Engine::Graphics::Bloom::Process(FrameBuffer &framebuffer, FrameBufferTexture *input, glm::ivec2 frame)
    {
        brightnessThreshold.SetInput(input);
        brightnessThreshold.Use(framebuffer);
        container->GetShader("Brightness")->Use();
        textureRenderer->Render(brightnessThreshold.GetInput());
        container->GetShader("Brightness")->Disable();
        brightnessThreshold.Disable(framebuffer);

        std::vector<glm::ivec2> resolutions;
        for (size_t i = 0; i < 6; ++i)
        {
            glm::ivec2 resolution = glm::ivec2(frame.x >> i, frame.y >> i);
            glViewport(0, 0, resolution.x, resolution.y);
            downsample[i].GetOutput(0)->Set(resolution);
            downsample[i].Use(framebuffer);
            container->GetShader("Downsample")->Use();
            container->GetShader("Downsample")->SetFloat("level", i);
            textureRenderer->Render(downsample[i].GetInput());
            container->GetShader("Downsample")->Disable();
            downsample[i].Disable(framebuffer);
            resolutions.push_back(resolution);
        }


        for (int i = 4; i >= 0; --i)
        {
            glm::ivec2 resolution = resolutions[i];
            glViewport(0, 0, resolution.x, resolution.y);
            upsample[i].GetOutput(0)->Set(resolution);
            upsample[i].Use(framebuffer);
            container->GetShader("Upsample")->Use();
            container->GetShader("Upsample")->SetFloat("level", i);
            container->GetShader("Upsample")->SetVector4f("resolution", resolution.x, resolution.y, 1.0f / static_cast<float>(resolution.x), 1.0f / static_cast<float>(resolution.y));
            textureRenderer->Render(upsample[i].GetInput());
            container->GetShader("Upsample")->Disable();
            upsample[i].Disable(framebuffer);
        }
        glViewport(0, 0, frame.x, frame.y);
    }

    FrameBufferTexture *const Engine::Graphics::Bloom::GetResult()
    {
        return upsample[0].GetOutput(0);
    }
}
