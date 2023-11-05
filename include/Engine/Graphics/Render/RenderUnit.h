#pragma once

#include <vector>
#include <memory>
#include "Engine/Objects/Transform.h"
#include "Engine/Graphics/Render/RenderElement.h"
#include "Engine/Graphics/Elements/Interfaces/IModelMatrix.h"
#include <glm/glm.hpp>

namespace Engine::Graphics
{
    class RenderUnit
    {
    public:
        RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture);
        RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture, Objects::Transform *const transform);
        RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture, const glm::mat4 &matrix);
        RenderUnit(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture, glm::mat4 &&matrix);

        RenderUnit(const RenderUnit &rhs);
        RenderUnit(RenderUnit &&rhs) noexcept;
        RenderUnit &operator=(const RenderUnit &rhs);
        RenderUnit &operator=(RenderUnit &&rhs) noexcept;
        ~RenderUnit();

    public:
        void SetShader(size_t index);
        void SetRendable(size_t index);
        void SetMaterial(size_t index);
        void SetTexture(size_t index);
        void SetTransformMatrix(Objects::Transform *const transform);
        void SetTransformMatrix(const glm::mat4 &matrix);
        void SetTransformMatrix(glm::mat4 &&matrix);

    public:
        size_t GetShaderIndex() const;
        size_t GetRendableIndex() const;
        size_t GetMaterialIndex() const;
        size_t GetTextureIndex() const;

    public:
        RenderElement GetShader() const;
        RenderElement GetRendable() const;
        RenderElement GetMaterial() const;
        RenderElement GetTexture() const;
        std::shared_ptr<IModelMatrix> GetModelMatrix() const;

    public:
        bool ContainsShader() const;
        bool ContainsRendable() const;
        bool ContainsMaterial() const;
        bool ContainsTexture() const;
        bool ContainsModelMatrix() const;

    private:
        RenderElement shader;
        RenderElement rendable;
        RenderElement material;
        RenderElement texture;
        std::shared_ptr<IModelMatrix> modelMatrix;
    };
}