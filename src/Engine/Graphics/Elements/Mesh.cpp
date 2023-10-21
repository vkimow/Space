#include "Engine/Graphics/Elements/Mesh.h"
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    Mesh::Mesh(GLfloat *vertices, unsigned int *indices, size_t verticesCount, size_t indecesCount)
        : indecesCount(indecesCount)
        , VAO(0)
        , VBO(0)
        , IBO(0)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indecesCount, indices, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesCount, vertices, GL_STATIC_DRAW);

        LOG_DEBUG(verticesCount);
        LOG_DEBUG(indecesCount);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void *)(sizeof(vertices[0]) * 3));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void *)(sizeof(vertices[0]) * 5));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

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

    void Mesh::FullRender()
    {
        StartRender();
        Render();
        EndRender();
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