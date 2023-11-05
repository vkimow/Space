#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine/Graphics/Elements/Interfaces/IRendable.h"
#include "Engine/Graphics/Elements/Rendables/Vertex.h"
#include "Engine/Graphics/Elements/Rendables/Triangle.h"
#include <vector>

namespace Engine::Graphics
{
    class Mesh final: public IRendable
    {
    public:
        Mesh() = delete;
        Mesh(GLfloat *vertices, GLuint *indices, size_t verticesCount, size_t indecesCount);
        Mesh(GLfloat *vertices, Triangle *indices, size_t verticesCount, size_t trianglesCount);
        Mesh(Vertex *vertices, GLuint *indices, size_t verticesCount, size_t indecesCount);
        Mesh(Vertex *vertices, Triangle *indices, size_t verticesCount, size_t trianglesCount);
        Mesh(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices);
        Mesh(std::vector<GLfloat> &vertices, std::vector<Triangle> &triangles);
        Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);
        Mesh(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles);
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