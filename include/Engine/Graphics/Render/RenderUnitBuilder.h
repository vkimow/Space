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
        RenderUnit Create(size_t shader, size_t mesh);
        RenderUnit Create(size_t shader, size_t mesh, size_t material);
        RenderUnit Create(size_t shader, size_t mesh, size_t texture, size_t material);
        RenderUnit Create(size_t shader, size_t mesh, Objects::Transform *const transform);
        RenderUnit Create(size_t shader, size_t mesh, size_t material, Objects::Transform *const transform);
        RenderUnit Create(size_t shader, size_t mesh, size_t texture, size_t material, Objects::Transform *const transform);

        RenderUnit Create(const std::string& shader, const std::string& mesh);
        RenderUnit Create(const std::string& shader, const std::string& mesh, const std::string& material);
        RenderUnit Create(const std::string& shader, const std::string& mesh, const std::string& texture, const std::string& material);
        RenderUnit Create(const std::string& shader, const std::string& mesh, Objects::Transform *const transform);
        RenderUnit Create(const std::string& shader, const std::string& mesh, const std::string& material, Objects::Transform *const transform);
        RenderUnit Create(const std::string& shader, const std::string& mesh, const std::string& texture, const std::string& material, Objects::Transform *const transform);

    private:
        const Container * const container;
    };
}