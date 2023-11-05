#include "Engine/Graphics/Elements/Rendables/Line.h"
#include "Engine/Tools/Log/Logger.h"
#include <glm/gtc/type_ptr.hpp>

namespace Engine::Graphics
{
    Line::Line(const glm::vec3 &start, const glm::vec3 &end)
        : VAO(0)
        , VBO(0)
        , pointsCount(2)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        float vertices[] = {start.x, start.y, start.z, end.x, end.y, end.z};
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 3, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Line::Line(const std::vector<glm::vec3> &positions)
        : VAO(0)
        , VBO(0)
        , pointsCount(positions.size())
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        const float *vertices = glm::value_ptr(positions[0]);
        const size_t sizeOfElement = sizeof(vertices[0]) * 3;
        const size_t sizeOfVertices = sizeOfElement * pointsCount;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOfElement, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Line::~Line()
    {
        Clear();
    }

    void Line::StartRender()
    {
        glBindVertexArray(VAO);
    }

    void Line::Render()
    {
        glDrawArrays(GL_LINES, 0, pointsCount);
    }

    void Line::EndRender()
    {
        glBindVertexArray(0);
    }

    void Line::Clear()
    {
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
    }
}