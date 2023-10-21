#pragma once

#include <GL/glew.h>

namespace Engine::Graphics
{
    class Mesh
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
        void StartRender();
        void Render();
        void EndRender();

        void FullRender();
        void Clear();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indecesCount;
    };
}