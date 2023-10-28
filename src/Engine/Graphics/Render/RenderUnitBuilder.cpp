#include "Engine/Graphics/Render/RenderUnitBuilder.h"

namespace Engine::Graphics
{
    RenderUnitBuilder::RenderUnitBuilder(const Container *const container)
        :container(container)
    {}

    RenderUnitBuilder::~RenderUnitBuilder()
    {}

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t rendable)
    {
        return RenderUnit(shader, rendable);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t rendable, size_t material)
    {
        return RenderUnit(shader, rendable, material);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t rendable, size_t texture, size_t material)
    {
        return RenderUnit(shader, rendable, texture, material);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t rendable, Objects::Transform *const transform)
    {
        return RenderUnit(shader, rendable, transform);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t rendable, size_t material, Objects::Transform *const transform)
    {
        return RenderUnit(shader, rendable, material, transform);
    }

    RenderUnit RenderUnitBuilder::Create(size_t shader, size_t rendable, size_t texture, size_t material, Objects::Transform *const transform)
    {
        return RenderUnit(shader, rendable, texture, material, transform);
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& rendable)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetRendableIndex(rendable));
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& rendable, const std::string& material)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetRendableIndex(rendable), container->GetMaterialIndex(material));
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& rendable, const std::string& texture, const std::string& material)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetRendableIndex(rendable), container->GetTextureIndex(texture), container->GetMaterialIndex(material));
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& rendable, Objects::Transform *const transform)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetRendableIndex(rendable), transform);
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& rendable, const std::string& material, Objects::Transform *const transform)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetRendableIndex(rendable), container->GetMaterialIndex(material), transform);
    }

    RenderUnit RenderUnitBuilder::Create(const std::string& shader, const std::string& rendable, const std::string& texture, const std::string& material, Objects::Transform *const transform)
    {
        return RenderUnit(container->GetShaderIndex(shader), container->GetRendableIndex(rendable), container->GetTextureIndex(texture), container->GetMaterialIndex(material), transform);
    }

}

