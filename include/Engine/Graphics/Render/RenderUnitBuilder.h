#pragma once

#include <vector>
#include <memory>
#include "Engine/Graphics/Elements/Container.h"
#include "Engine/Graphics/Render/RenderUnit.h"
#include <string>

namespace Engine::Graphics
{
    class RenderUnitBuilder
    {
    public:

        RenderUnitBuilder(const Container *const container);
        RenderUnitBuilder(const RenderUnitBuilder &rhs) = delete;
        RenderUnitBuilder(RenderUnitBuilder &&rhs) noexcept = delete;
        RenderUnitBuilder &operator=(const RenderUnitBuilder &rhs) = delete;
        RenderUnitBuilder &operator=(RenderUnitBuilder &&rhs) noexcept = delete;
        ~RenderUnitBuilder();

    public:
        RenderUnit Create(RenderElement shader, RenderElement rendable);
        RenderUnit Create(RenderElement shader, RenderElement rendable, RenderElement material);
        RenderUnit Create(RenderElement shader, RenderElement rendable, RenderElement material, RenderElement texture);

        template<typename TransformMatrixSource>
        RenderUnit Create(RenderElement shader, RenderElement rendable, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(shader, rendable, RenderElement(), RenderElement(), std::forward<TransformMatrixSource>(transformMatrixSource));
        }

        template<typename TransformMatrixSource>
        RenderUnit Create(RenderElement shader, RenderElement rendable, RenderElement material, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(shader, rendable, material, RenderElement(), std::forward<TransformMatrixSource>(transformMatrixSource));
        }

        template<typename TransformMatrixSource>
        RenderUnit Create(RenderElement shader, RenderElement rendable, RenderElement texture, RenderElement material, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(shader, rendable, material, texture, std::forward<TransformMatrixSource>(transformMatrixSource));
        }


        RenderUnit Create(const char *shader, const char *rendable);
        RenderUnit Create(const char *shader, const char *rendable, const char *material);
        RenderUnit Create(const char *shader, const char *rendable, const char *material, const char *texture);
        RenderUnit Create(const std::string& shader, const std::string& rendable);
        RenderUnit Create(const std::string& shader, const std::string& rendable, const std::string& material);
        RenderUnit Create(const std::string& shader, const std::string& rendable, const std::string& material, const std::string& texture);

        template<typename TransformMatrixSource>
        RenderUnit Create(const char *shader, const char *rendable, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(shader ? container->GetShaderIndex(shader) : RenderElement(),
                rendable ? container->GetRendableIndex(rendable) : RenderElement(),
                RenderElement(),
                RenderElement(),
                std::forward<TransformMatrixSource>(transformMatrixSource)
            );
        }

        template<typename TransformMatrixSource>
        RenderUnit Create(const char *shader, const char *rendable, const char *material, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(shader ? container->GetShaderIndex(shader) : RenderElement(),
                rendable ? container->GetRendableIndex(rendable) : RenderElement(),
                material ? container->GetMaterialIndex(material) : RenderElement(),
                RenderElement(),
                std::forward<TransformMatrixSource>(transformMatrixSource)
            );
        }

        template<typename TransformMatrixSource>
        RenderUnit Create(const char *shader, const char *rendable, const char *material, const char *texture, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(shader ? container->GetShaderIndex(shader) : RenderElement(),
                rendable ? container->GetRendableIndex(rendable) : RenderElement(),
                texture ? container->GetTextureIndex(texture) : RenderElement(),
                material ? container->GetMaterialIndex(material) : RenderElement(),
                std::forward<TransformMatrixSource>(transformMatrixSource)
            );
        }

        template<typename TransformMatrixSource>
        RenderUnit Create(const std::string &shader, const std::string &rendable, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(container->GetShaderIndex(shader),
                container->GetRendableIndex(rendable),
                RenderElement(),
                RenderElement(),
                std::forward<TransformMatrixSource>(transformMatrixSource)
            );
        }

        template<typename TransformMatrixSource>
        RenderUnit Create(const std::string &shader, const std::string &rendable, const std::string &material, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(container->GetShaderIndex(shader),
                container->GetRendableIndex(rendable),
                container->GetMaterialIndex(material),
                RenderElement(),
                std::forward<TransformMatrixSource>(transformMatrixSource)
            );
        }

        template<typename TransformMatrixSource>
        RenderUnit Create(const std::string &shader, const std::string &rendable, const std::string &material, const std::string &texture, TransformMatrixSource &&transformMatrixSource)
        {
            return RenderUnit(container->GetShaderIndex(shader),
                container->GetRendableIndex(rendable),
                container->GetMaterialIndex(material),
                container->GetTextureIndex(texture),
                std::forward<TransformMatrixSource>(transformMatrixSource)
            );
        }

    private:
        const Container *const container;
    };
}