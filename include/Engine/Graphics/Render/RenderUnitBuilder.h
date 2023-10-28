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
        RenderUnit Create(size_t shader, size_t rendable);
        RenderUnit Create(size_t shader, size_t rendable, size_t material);
        RenderUnit Create(size_t shader, size_t rendable, size_t texture, size_t material);
        RenderUnit Create(size_t shader, size_t rendable, Objects::Transform *const transform);
        RenderUnit Create(size_t shader, size_t rendable, size_t material, Objects::Transform *const transform);
        RenderUnit Create(size_t shader, size_t rendable, size_t texture, size_t material, Objects::Transform *const transform);

        RenderUnit Create(const std::string& shader, const std::string& rendable);
        RenderUnit Create(const std::string& shader, const std::string& rendable, const std::string& material);
        RenderUnit Create(const std::string& shader, const std::string& rendable, const std::string& texture, const std::string& material);
        RenderUnit Create(const std::string& shader, const std::string& rendable, Objects::Transform *const transform);
        RenderUnit Create(const std::string& shader, const std::string& rendable, const std::string& material, Objects::Transform *const transform);
        RenderUnit Create(const std::string& shader, const std::string& rendable, const std::string& texture, const std::string& material, Objects::Transform *const transform);

    private:
        const Container * const container;
    };
}