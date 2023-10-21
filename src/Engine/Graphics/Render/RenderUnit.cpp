#include "Engine/Graphics/Render/RenderUnit.h"
#include "Engine/Tools/Log/Logger.h"
#include "Engine/Graphics/Elements/Container.h"

namespace Engine::Graphics
{
    RenderUnit::RenderUnit(size_t shader, size_t mesh)
        : shader(shader)
        , mesh(mesh)
        , texture()
        , material()
        , transform(nullptr)
    {}
    RenderUnit::RenderUnit(size_t shader, size_t mesh, size_t material)
        : shader(shader)
        , mesh(mesh)
        , texture()
        , material(material)
        , transform(nullptr)
    {}
    RenderUnit::RenderUnit(size_t shader, size_t mesh, size_t texture, size_t material)
        : shader(shader)
        , mesh(mesh)
        , texture(texture)
        , material(material)
        , transform(nullptr)
    {}
    RenderUnit::RenderUnit(size_t shader, size_t mesh, Objects::Transform *const transform)
        : shader(shader)
        , mesh(mesh)
        , texture()
        , material()
        , transform(transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform in null!");
        }
    }

    RenderUnit::RenderUnit(size_t shader, size_t mesh, size_t material, Objects::Transform *const transform)
        : shader(shader)
        , mesh(mesh)
        , texture()
        , material(material)
        , transform(transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform in null!");
        }
    }

    RenderUnit::RenderUnit(size_t shader, size_t mesh, size_t texture, size_t material, Objects::Transform *const transform)
        : shader(shader)
        , mesh(mesh)
        , texture(texture)
        , material(material)
        , transform(transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform in null!");
        }
    }

    RenderUnit::RenderUnit(const RenderUnit &rhs)
        : shader(rhs.shader)
        , mesh(rhs.mesh)
        , texture(rhs.texture)
        , material(rhs.material)
        , transform(rhs.transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform in null!");
        }
    }

    RenderUnit::RenderUnit(RenderUnit &&rhs) noexcept
        : shader(std::move(rhs.shader))
        , mesh(std::move(rhs.mesh))
        , texture(std::move(rhs.texture))
        , material(std::move(rhs.material))
        , transform(rhs.transform)
    {
        if (!transform)
        {
            LOG_ERROR("Transform in null!");
        }
        rhs.transform = nullptr;
    }

    RenderUnit &RenderUnit::operator=(const RenderUnit &rhs)
    {
        shader = rhs.shader;
        mesh = rhs.mesh;
        texture = rhs.texture;
        material = rhs.material;
        transform = rhs.transform;
        if (!transform)
        {
            LOG_ERROR("Transform in null!");
        }
        return *this;
    }

    RenderUnit &RenderUnit::operator=(RenderUnit &&rhs) noexcept
    {
        shader = std::move(rhs.shader);
        mesh = std::move(rhs.mesh);
        texture = std::move(rhs.texture);
        material = std::move(rhs.material);
        transform = rhs.transform;
        if (!transform)
        {
            LOG_ERROR("Transform in null!");
        }
        rhs.transform = nullptr;
        return *this;
    }

    RenderUnit::~RenderUnit()
    {}

    void RenderUnit::SetShader(size_t index)
    {
        shader = RenderElement(index);
    }

    void RenderUnit::SetMesh(size_t index)
    {
        mesh = RenderElement(index);
    }

    void RenderUnit::SetTexture(size_t index)
    {
        texture = RenderElement(index);
    }

    void RenderUnit::SetMaterial(size_t index)
    {
        material = RenderElement(index);
    }

    void RenderUnit::SetTransform(Objects::Transform *const transform)
    {
        this->transform = transform;
    }

    size_t RenderUnit::GetShaderIndex() const
    {
        if (!shader)
        {
            LOG_ERROR("RenderUnit doesn't contain shader");
        }
        return shader.GetIndex();
    }

    size_t RenderUnit::GetMeshIndex() const
    {
        if (!mesh)
        {
            LOG_ERROR("RenderUnit doesn't contain shader");
        }
        return mesh.GetIndex();
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

    RenderElement RenderUnit::GetMesh() const
    {
        return mesh;
    }

    RenderElement RenderUnit::GetTexture() const
    {
        return texture;
    }

    RenderElement RenderUnit::GetMaterial() const
    {
        return material;
    }

    Objects::Transform *const RenderUnit::GetTransform() const
    {
        return transform;
    }

    bool RenderUnit::ContainsShader() const
    {
        return shader.IsExist();
    }

    bool RenderUnit::ContainsMesh() const
    {
        return mesh.IsExist();
    }

    bool RenderUnit::ContainsTexture() const
    {
        return texture.IsExist();
    }

    bool RenderUnit::ContainsMaterial() const
    {
        return material.IsExist();
    }

    bool RenderUnit::ContainsTransform() const
    {
        return transform;
    }
}