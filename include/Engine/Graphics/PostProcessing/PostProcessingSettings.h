#pragma once

#include <glm/glm.hpp>

namespace Engine::Graphics
{
    class Container;
    class PostProcessingSettings
    {
        friend class PostProcessingManager;

    private:
        PostProcessingSettings(Container *container);
        PostProcessingSettings(const PostProcessingSettings &rhs) = delete;
        PostProcessingSettings(PostProcessingSettings &&rhs) noexcept = delete;
        PostProcessingSettings &operator=(const PostProcessingSettings &rhs) = delete;
        PostProcessingSettings &operator=(PostProcessingSettings &&rhs) noexcept = delete;
        ~PostProcessingSettings();

    public:
        void SetToDefault();

    public:
        void SetGamma(float value);
        void SetExposure(float value);
        void SetBloomThreshold(float value);

    public:
        float GetGamma();
        float GetExposure();
        float GetBloomThreshold();

    private:
        Container *const container;

    private:
        float gamma;
        float exposure;
        float bloomThreshold;
    };
}