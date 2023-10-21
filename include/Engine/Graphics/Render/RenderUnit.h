#pragma once

#include <vector>
#include <memory>
#include "Engine/Objects/Transform.h"
#include "Engine/Graphics/Render/RenderElement.h"

namespace Engine::Graphics
{
    class RenderUnit
    {
    public:
        RenderUnit(size_t shader, size_t mesh);
        RenderUnit(size_t shader, size_t mesh, size_t material);
        RenderUnit(size_t shader, size_t mesh, size_t texture, size_t material);
        RenderUnit(size_t shader, size_t mesh, Objects::Transform *const transform);
        RenderUnit(size_t shader, size_t mesh, size_t material, Objects::Transform *const transform);
        RenderUnit(size_t shader, size_t mesh, size_t texture, size_t material, Objects::Transform *const transform);

        RenderUnit(const RenderUnit &rhs);
        RenderUnit(RenderUnit &&rhs) noexcept;
        RenderUnit &operator=(const RenderUnit &rhs);
        RenderUnit &operator=(RenderUnit &&rhs) noexcept;
        ~RenderUnit();

    public:
        void SetShader(size_t index);
        void SetMesh(size_t index);
        void SetTexture(size_t index);
        void SetMaterial(size_t index);
        void SetTransform(Objects::Transform *const transform);

    public:
        size_t GetShaderIndex() const;
        size_t GetMeshIndex() const;
        size_t GetTextureIndex() const;
        size_t GetMaterialIndex() const;

    public:
        RenderElement GetShader() const;
        RenderElement GetMesh() const;
        RenderElement GetTexture() const;
        RenderElement GetMaterial() const;
        Objects::Transform *const GetTransform() const;

    public:
        bool ContainsShader() const;
        bool ContainsMesh() const;
        bool ContainsTexture() const;
        bool ContainsMaterial() const;
        bool ContainsTransform() const;

    private:
        RenderElement shader;
        RenderElement mesh;
        RenderElement texture;
        RenderElement material;
        Objects::Transform *transform;
    };
}