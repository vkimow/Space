#include "Engine/Graphics/Render/RenderUnitBuilder.h"

namespace Engine::Graphics
{
    RenderUnitBuilder::RenderUnitBuilder(const Container *const container)
        :container(container)
    {}

    RenderUnitBuilder::~RenderUnitBuilder()
    {}

    RenderUnit RenderUnitBuilder::Create(RenderElement shader, RenderElement rendable)
    {
        return RenderUnit(shader, rendable, RenderElement(), RenderElement());
    }

    RenderUnit RenderUnitBuilder::Create(RenderElement shader, RenderElement rendable, RenderElement material)
    {
        return RenderUnit(shader, rendable, material, RenderElement());
    }

    RenderUnit RenderUnitBuilder::Create(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture)
    {
        return RenderUnit(shader, rendable, material, texture);
    }

    RenderUnit RenderUnitBuilder::Create(const char *shader, const char *rendable)
    {
        return RenderUnit(shader ? container->GetShaderIndex(shader) : RenderElement(),
            rendable ? container->GetRendableIndex(rendable) : RenderElement(),
            RenderElement(),
            RenderElement()
        );
    }

    RenderUnit RenderUnitBuilder::Create(const char *shader, const char *rendable, const char *material)
    {
        return RenderUnit(shader ? container->GetShaderIndex(shader) : RenderElement(),
            rendable ? container->GetRendableIndex(rendable) : RenderElement(),
            material ? container->GetMaterialIndex(material) : RenderElement(),
            RenderElement()
        );
    }

    RenderUnit RenderUnitBuilder::Create(const char *shader, const char *rendable, const char *material, const char *texture)
    {
        return RenderUnit(shader ? container->GetShaderIndex(shader) : RenderElement(),
            rendable ? container->GetRendableIndex(rendable) : RenderElement(),
            material ? container->GetMaterialIndex(material) : RenderElement(),
            texture ? container->GetTextureIndex(texture) : RenderElement()
        );
    }

    RenderUnit RenderUnitBuilder::Create(const std::string &shader, const std::string &rendable)
    {
        return RenderUnit(container->GetShaderIndex(shader),
            container->GetRendableIndex(rendable),
            RenderElement(),
            RenderElement()
        );
    }

    RenderUnit RenderUnitBuilder::Create(const std::string &shader, const std::string &rendable, const std::string &material)
    {
        return RenderUnit(container->GetShaderIndex(shader),
            container->GetRendableIndex(rendable),
            container->GetMaterialIndex(material),
            RenderElement()
        );
    }

    RenderUnit RenderUnitBuilder::Create(const std::string &shader, const std::string &rendable, const std::string &material, const std::string &texture)
    {
        return RenderUnit(container->GetShaderIndex(shader),
            container->GetRendableIndex(rendable),
            container->GetMaterialIndex(material),
            container->GetTextureIndex(texture)
        );
    }


}

