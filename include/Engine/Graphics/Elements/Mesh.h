#pragma once

#include "IRendable.h"
#include <GL/glew.h>

namespace Engine::Graphics
{
    class Mesh final : public IRendable
    {
        friend class Container;

    private:
        Mesh() = delete;
        Mesh(GLfloat *vertices, unsigned int *indices, size_t verticesCount, size_t indecesCount);
        Mesh(const Mesh &rhs) = delete;
        Mesh(Mesh &&rhs) = delete;
        Mesh &operator=(const Mesh &rhs) = delete;
        Mesh &operator=(Mesh &&rhs) = delete;
        ~Mesh();

    public:
        void StartRender() override final;
        void Render() override final;
        void EndRender() override final;

    private:
        void Clear();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indecesCount;
    };
}