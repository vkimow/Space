#pragma once

#include "IRendable.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Engine::Graphics
{
    class Line : public IRendable
    {
        friend class Container;

    private:
        Line() = delete;
        Line(const glm::vec3& start, const glm::vec3& end);
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
    };
}