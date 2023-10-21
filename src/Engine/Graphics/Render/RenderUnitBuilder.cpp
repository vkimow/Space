#include "Engine/Graphics/Render/RenderUnitBuilder.h"

namespace Engine::Graphics
{
    RenderUnitBuilder::RenderUnitBuilder(const Container *const container)
        :container(container)
    {}

    RenderUnitBuilder::~RenderUnitBuilder()
    {}

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t mesh)
    {
        return RenderUnit(shader, mesh);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t mesh, size_t material)
    {
        return RenderUnit(shader, mesh, material);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t mesh, size_t texture, size_t material)
    {
        return RenderUnit(shader, mesh, texture, material);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t mesh, Objects::Transform *const transform)
    {
        return RenderUnit(shader, mesh, transform);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t mesh, size_t material, Objects::Transform *const transform)
    {
        return RenderUnit(shader, mesh, material, transform);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t mesh, size_t texture, size_t material, Objects::Transform *const transform)
    {
        return RenderUnit(shader, mesh, texture, material, transform);
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& mesh)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetMeshIndex(mesh));
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& mesh, const std::string& material)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetMeshIndex(mesh), container->GetMaterialIndex(material));
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& mesh, const std::string& texture, const std::string& material)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetMeshIndex(mesh), container->GetTextureIndex(texture), container->GetMaterialIndex(material));
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& mesh, Objects::Transform *const transform)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetMeshIndex(mesh), transform);
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& mesh, const std::string& material, Objects::Transform *const transform)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetMeshIndex(mesh), container->GetMaterialIndex(material), transform);
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& mesh, const std::string& texture, const std::string& material, Objects::Transform *const transform)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetMeshIndex(mesh), container->GetTextureIndex(texture), container->GetMaterialIndex(material), transform);
    }

}

