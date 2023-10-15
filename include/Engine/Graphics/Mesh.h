#pragma once

#include <GL/glew.h>

namespace Engine::Graphics
{
    class Mesh
    {
    public:
        Mesh();
        Mesh(const Mesh &rhs) = default;
        Mesh(Mesh &&rhs) = default;
        Mesh &operator=(const Mesh &rhs) = default;
        Mesh &operator=(Mesh &&rhs) = default;
        ~Mesh();

    public:
        void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
        void RenderMesh();
        void ClearMesh();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;
    };
}