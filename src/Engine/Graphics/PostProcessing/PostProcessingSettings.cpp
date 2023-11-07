#include "Engine/Graphics/PostProcessing/PostProcessingSettings.h"
#include "Engine/Graphics/Elements/Container.h"

namespace Engine::Graphics
{
    PostProcessingSettings::PostProcessingSettings(Container *container)
        : container(container)
    {}

    PostProcessingSettings::~PostProcessingSettings()
    {}

    void PostProcessingSettings::SetToDefault()
    {
        SetGamma(2.2f);
        SetExposure(1.0f);
        SetBloomThreshold(0.0f);
    }

    void PostProcessingSettings::SetGamma(float value)
    {
        gamma = value;
        auto  shader = container->GetShader("ColorCorrection");
        shader->Use();
        shader->SetFloat("gamma", value);
        shader->Disable();
    }

    void PostProcessingSettings::SetExposure(float value)
    {
        exposure = value;
        auto  shader = container->GetShader("ColorCorrection");
        shader->Use();
        shader->SetFloat("exposure", value);
        shader->Disable();
    }

    void PostProcessingSettings::SetBloomThreshold(float value)
    {
        bloomThreshold = value;
        auto  shader = container->GetShader("Brightness");
        shader->Use();
        shader->SetFloat("threshold", value);
        shader->Disable();
    }

    float PostProcessingSettings::GetGamma()
    {
        return gamma;
    }

    float PostProcessingSettings::GetExposure()
    {
        return exposure;
    }

    float PostProcessingSettings::GetBloomThreshold()
    {
        return bloomThreshold;
    }
}

