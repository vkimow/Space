#pragma once

#include "Engine/Graphics/Elements/Interfaces/IRendable.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

namespace Engine::Graphics
{
    class Line : public IRendable
    {
    public:
        Line() = delete;
        Line(const glm::vec3 &start, const glm::vec3 &end);
        Line(const std::vector<glm::vec3>& positions);

        Line(const Line &rhs) = delete;
        Line(Line &&rhs) = delete;
        Line &operator=(const Line &rhs) = delete;
        Line &operator=(Line &&rhs) = delete;
        ~Line();

    public:
        void StartRender() override final;
        void Render() override final;
        void EndRender() override final;

    private:
        void Clear();

    private:
        GLuint VAO, VBO;
        const size_t pointsCount;
    };
}