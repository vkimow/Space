#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Engine/Tools/Events/MemberFunction.h"
#include "Engine/Graphics/PostProcessing/IFrameBufferHandler.h"

namespace Engine::Graphics
{
    class FrameBufferTextureManager;
    class RenderBufferHandler : IFrameBufferHandler
    {
        friend class PostProcessingManager;

    private:
        RenderBufferHandler(FrameBufferTextureManager *textureManager);
        RenderBufferHandler(const RenderBufferHandler &rhs) = delete;
        RenderBufferHandler(RenderBufferHandler &&rhs) noexcept = delete;
        RenderBufferHandler &operator=(const RenderBufferHandler &rhs) = delete;
        RenderBufferHandler &operator=(RenderBufferHandler &&rhs) noexcept = delete;
        ~RenderBufferHandler();

    public:
        void SetRenderBuffer(glm::ivec2 frame);
        void Use(FrameBuffer &framebuffer) override final;
        void Disable(FrameBuffer &framebuffer) override final;

        void SetOutputCount(size_t value);
        const std::vector<FrameBufferTexture *> &GetOutput() const override final;
        FrameBufferTexture *const GetOutput(size_t index) const override final;
        size_t GetOutputCount() const override final;

    private:
        GLuint rbo;
        FrameBufferTextureManager *textureManager;
        std::vector<FrameBufferTexture*> outputTextures;
    };
}