#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Engine/Tools/Events/MemberFunction.h"
#include "Engine/Graphics/PostProcessing/IFrameBufferHandler.h"

namespace Engine::Graphics
{
    class FrameBufferTextureManager;
    class PostProcessingBufferHandler: public IFrameBufferHandler
    {
    public:
        PostProcessingBufferHandler(FrameBufferTextureManager *textureManager);
        PostProcessingBufferHandler(const PostProcessingBufferHandler &rhs) = delete;
        PostProcessingBufferHandler(PostProcessingBufferHandler &&rhs) noexcept;
        PostProcessingBufferHandler &operator=(const PostProcessingBufferHandler &rhs) = delete;
        PostProcessingBufferHandler &operator=(PostProcessingBufferHandler &&rhs) noexcept;
        ~PostProcessingBufferHandler();

    public:
        void SetInput(IFrameBufferHandler* bufferHandler);
        void SetInput(FrameBufferTexture *textures);
        void SetInput(FrameBufferTexture *textures, size_t count);
        void SetInput(const std::vector<FrameBufferTexture*> &textures);
        void SetInput(auto begin, auto end)
        {
            inputTextures.clear();
            AddInput(begin, end);
        }

        void AddInput(const IFrameBufferHandler& bufferHandler);
        void AddInput(IFrameBufferHandler *bufferHandler);
        void AddInput(FrameBufferTexture *texture);
        void AddInput(FrameBufferTexture *textures, size_t count);
        void AddInput(const std::vector<FrameBufferTexture *> &textures);
        void AddInput(auto begin, auto end)
        {
            inputTextures.insert(inputTextures.end(), begin, end);
        }


    public:
        void Use(FrameBuffer &framebuffer) override final;
        void Disable(FrameBuffer &framebuffer) override final;

        const std::vector<FrameBufferTexture *> &GetInput() const;
        FrameBufferTexture *const GetInput(size_t index) const;
        size_t GetInputCount() const;

        void SetOutputCount(size_t value);
        const std::vector<FrameBufferTexture *> &GetOutput() const override final;
        FrameBufferTexture *const GetOutput(size_t index) const override final;
        size_t GetOutputCount() const override final;

    private:
        FrameBufferTextureManager *textureManager;
        std::vector<FrameBufferTexture *> inputTextures;
        std::vector<FrameBufferTexture *> outputTextures;
    };
}