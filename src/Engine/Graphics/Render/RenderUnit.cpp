#include "Engine/Graphics/Render/RenderUnit.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Graphics/Elements/Container.h"
#include "Engine/Graphics/Elements/ModelMatrix/ModelMatrixHeader.h"

namespace Engine::Graphics
{
    RenderUnit::RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture)
        : shader(shader)
        , rendable(rendable)
        , material(material)
        , texture(texture)
        , modelMatrix(nullptr)
    {}

    RenderUnit::RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture, Objects::Transform *const transform)
        : shader(shader)
        , rendable(rendable)
        , material(material)
        , texture(texture)
        , modelMatrix(std::make_shared<TransformMatrixFromTransformPtr>(transform))
    {}

    RenderUnit::RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture, const glm::mat4 &matrix)
        : shader(shader)
        , rendable(rendable)
        , material(material)
        , texture(texture)
        , modelMatrix(std::make_shared<TransformMatrixFromMatrix>(matrix))
    {}

    RenderUnit::RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture, glm::mat4 &&matrix)
        : shader(shader)
        , rendable(rendable)
        , material(material)
        , texture(texture)
        , modelMatrix(std::make_shared<TransformMatrixFromMatrix>(std::move(matrix)))
    {}

    RenderUnit::RenderUnit(const RenderUnit &rhs)
        : shader(rhs.shader)
        , rendable(rhs.rendable)
        , material(rhs.material)
        , texture(rhs.texture)
        , modelMatrix(rhs.modelMatrix)
    {}

    RenderUnit::RenderUnit(RenderUnit &&rhs) noexcept
        : shader(std::move(rhs.shader))
        , rendable(std::move(rhs.rendable))
        , material(std::move(rhs.material))
        , texture(std::move(rhs.texture))
        , modelMatrix(std::move(rhs.modelMatrix))
    {}

    RenderUnit &RenderUnit::operator=(const RenderUnit &rhs)
    {
        shader = rhs.shader;
        rendable = rhs.rendable;
        material = rhs.material;
        texture = rhs.texture;
        modelMatrix = rhs.modelMatrix;
        return *this;
    }

    RenderUnit &RenderUnit::operator=(RenderUnit &&rhs) noexcept
    {
        shader = std::move(rhs.shader);
        rendable = std::move(rhs.rendable);
        material = std::move(rhs.material);
        texture = std::move(rhs.texture);
        modelMatrix = std::move(rhs.modelMatrix);
        return *this;
    }

    RenderUnit::~RenderUnit()
    {}

    void RenderUnit::SetShader(size_t index)
    {
        shader = RenderElement(index);
    }

    void RenderUnit::SetRendable(size_t index)
    {
        rendable = RenderElement(index);
    }

    void RenderUnit::SetTexture(size_t index)
    {
        texture = RenderElement(index);
    }

    void RenderUnit::SetMaterial(size_t index)
    {
        material = RenderElement(index);
    }

    void RenderUnit::SetTransformMatrix(Objects::Transform *const transform)
    {
        modelMatrix = std::make_shared<TransformMatrixFromTransformPtr>(transform);
    }

    void RenderUnit::SetTransformMatrix(const glm::mat4 &matrix)
    {
        modelMatrix = std::make_shared<TransformMatrixFromMatrix>(matrix);
    }

    void RenderUnit::SetTransformMatrix(glm::mat4 &&matrix)
    {
        modelMatrix = std::make_shared<TransformMatrixFromMatrix>(std::move(matrix));
    }

    size_t RenderUnit::GetShaderIndex() const
    {
        if (!shader)
        {
            LOG_ERROR("RenderUnit doesn't contain shader");
        }
        return shader.GetIndex();
    }

    size_t RenderUnit::GetRendableIndex() const
    {
        if (!rendable)
        {
            LOG_ERROR("RenderUnit doesn't contain shader");
        }
        return rendable.GetIndex();
    }

    size_t RenderUnit::GetTextureIndex() const
    {
        if (!texture)
        {
            LOG_ERROR("RenderUnit doesn't contain texture");
        }
        return texture.GetIndex();
    }

    size_t RenderUnit::GetMaterialIndex() const
    {
        if (!material)
        {
            LOG_ERROR("RenderUnit doesn't contain material");
        }
        return material.GetIndex();
    }

    RenderElement RenderUnit::GetShader() const
    {
        return shader;
    }

    RenderElement RenderUnit::GetRendable() const
    {
        return rendable;
    }

    RenderElement RenderUnit::GetTexture() const
    {
        return texture;
    }

    std::shared_ptr<IModelMatrix> RenderUnit::GetModelMatrix() const
    {
        return modelMatrix;
    }

    RenderElement RenderUnit::GetMaterial() const
    {
        return material;
    }

    bool RenderUnit::ContainsShader() const
    {
        return shader.IsExist();
    }

    bool RenderUnit::ContainsRendable() const
    {
        return rendable.IsExist();
    }

    bool RenderUnit::ContainsTexture() const
    {
        return texture.IsExist();
    }

    bool RenderUnit::ContainsMaterial() const
    {
        return material.IsExist();
    }

    bool RenderUnit::ContainsModelMatrix() const
    {
        return modelMatrix != nullptr;
    }
}