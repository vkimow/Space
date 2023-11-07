#include "Engine/Graphics/PostProcessing/PostProcessingBufferHandler.h"
#include "Engine/Tools/Other/GL.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Graphics/PostProcessing/FrameBuffer.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTexture.h"
#include "Engine/Graphics/PostProcessing/FrameBufferTextureManager.h"

namespace Engine::Graphics
{

    PostProcessingBufferHandler::PostProcessingBufferHandler(FrameBufferTextureManager *textureManager)
        : textureManager(textureManager)
        , inputTextures()
        , outputTextures()
    {}

    PostProcessingBufferHandler::PostProcessingBufferHandler(PostProcessingBufferHandler && rhs) noexcept
        : textureManager(rhs.textureManager)
        , inputTextures(std::move(rhs.inputTextures))
        , outputTextures(std::move(rhs.outputTextures))
    {
        rhs.outputTextures.clear();
    }

    PostProcessingBufferHandler &PostProcessingBufferHandler::operator=(PostProcessingBufferHandler &&rhs) noexcept
    {
        inputTextures = std::move(rhs.inputTextures);
        outputTextures = std::move(rhs.outputTextures);
        rhs.outputTextures.clear();
        return *this;
    }

    PostProcessingBufferHandler::~PostProcessingBufferHandler()
    {
        for (auto it = outputTextures.begin(); it != outputTextures.end(); ++it)
        {
            delete *it;
        }
        outputTextures.clear();
    }

    void PostProcessingBufferHandler::SetInput(IFrameBufferHandler *bufferHandler)
    {
        inputTextures.clear();
        AddInput(bufferHandler);
    }

    void PostProcessingBufferHandler::SetInput(FrameBufferTexture *texture)
    {
        inputTextures.clear();
        AddInput(texture);
    }

    void PostProcessingBufferHandler::SetInput(FrameBufferTexture * textures, size_t count)
    {
        inputTextures.clear();
        AddInput(textures, count);
    }

    void PostProcessingBufferHandler::SetInput(const std::vector<FrameBufferTexture *>&textures)
    {
        inputTextures.clear();
        AddInput(textures);
    }

    void PostProcessingBufferHandler::AddInput(const IFrameBufferHandler &bufferHandler)
    {
        AddInput(bufferHandler.GetOutput());
    }

    void PostProcessingBufferHandler::AddInput(IFrameBufferHandler *bufferHandler)
    {
        AddInput(bufferHandler->GetOutput());
    }

    void PostProcessingBufferHandler::AddInput(FrameBufferTexture *texture)
    {
        inputTextures.push_back(texture);
    }

    void PostProcessingBufferHandler::AddInput(FrameBufferTexture * textures, size_t count)
    {
        inputTextures.insert(inputTextures.end(), count, textures);
    }

    void PostProcessingBufferHandler::AddInput(const std::vector<FrameBufferTexture *>&textures)
    {
        AddInput(textures.begin(), textures.end());
    }

    void PostProcessingBufferHandler::Use(FrameBuffer &framebuffer)
    {
        framebuffer.AttachTextures(outputTextures);
        framebuffer.Use();
    }

    void PostProcessingBufferHandler::Disable(FrameBuffer &framebuffer)
    {
        framebuffer.Disable();
    }

    const std::vector<FrameBufferTexture *> &PostProcessingBufferHandler::GetInput() const
    {
        return inputTextures;
    }

    FrameBufferTexture *const PostProcessingBufferHandler::GetInput(size_t index) const
    {
        return inputTextures[index];
    }

    size_t PostProcessingBufferHandler::GetInputCount() const
    {
        return inputTextures.size();
    }

    void PostProcessingBufferHandler::SetOutputCount(size_t value)
    {
        if (value > outputTextures.size())
        {
            for (size_t i = outputTextures.size(); i < value; ++i)
            {
                outputTextures.push_back(new FrameBufferTexture(textureManager));
            }
        }
        else
        {
            for (auto it = outputTextures.begin() + value; it != outputTextures.end(); ++it)
            {
                delete *it;
            }
            outputTextures.erase(outputTextures.begin() + value, outputTextures.end());
        }
    }

    const std::vector<FrameBufferTexture *> &PostProcessingBufferHandler::GetOutput() const
    {
        return outputTextures;
    }

    FrameBufferTexture *const PostProcessingBufferHandler::GetOutput(size_t index) const
    {
        return outputTextures[index];
    }

    size_t PostProcessingBufferHandler::GetOutputCount() const
    {
        return size_t();
    }
}