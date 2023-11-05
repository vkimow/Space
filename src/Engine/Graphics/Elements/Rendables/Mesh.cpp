#include "Engine/Graphics/Elements/Rendables/Mesh.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    static void AttribPointersInitialization()
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    }

    Mesh::Mesh(GLfloat *vertices, GLuint *indices, size_t verticesCount, size_t indecesCount)
        : indecesCount(indecesCount)
        , VAO(0)
        , VBO(0)
        , IBO(0)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indecesCount, indices, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesCount, vertices, GL_STATIC_DRAW);

        AttribPointersInitialization();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Mesh::Mesh(GLfloat *vertices, Triangle *triangles, size_t verticesCount, size_t trianglesCount)
        : Mesh(vertices, triangles->GetPointer(), verticesCount, trianglesCount * 3)
    {}

    Mesh::Mesh(Vertex *vertices, GLuint *indices, size_t verticesCount, size_t indecesCount)
        : Mesh(vertices->GetPointer(), indices, verticesCount * 8, indecesCount)
    {}

    Mesh::Mesh(Vertex *vertices, Triangle *triangles, size_t verticesCount, size_t trianglesCount)
        : Mesh(vertices->GetPointer(), triangles->GetPointer(), verticesCount * 8, trianglesCount * 3)
    {}

    Mesh::Mesh(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices)
        : Mesh(vertices.data(), indices.data(), vertices.size(), indices.size())
    {}

    Mesh::Mesh(std::vector<GLfloat> &vertices, std::vector<Triangle> &triangles)
        : Mesh(vertices.data(), triangles.data(), vertices.size(), triangles.size())
    {}

    Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices)
        : Mesh(vertices.data(), indices.data(), vertices.size(), indices.size())
    {}

    Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles)
        : Mesh(vertices.data(), triangles.data(), vertices.size(), triangles.size())
    {}

    Mesh::~Mesh()
    {
        Clear();
    }

    void Mesh::StartRender()
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    }

    void Mesh::Render()
    {
        glDrawElements(GL_TRIANGLES, indecesCount, GL_UNSIGNED_INT, 0);
    }

    void Mesh::EndRender()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Mesh::Clear()
    {
        if (IBO != 0)
        {
            glDeleteBuffers(1, &IBO);
            IBO = 0;
        }

        if (VBO != 0)
        {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }

        if (VAO != 0)
        {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }

        indecesCount = 0;
    }
}