#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <initializer_list>

namespace Engine::Graphics
{
    struct Vertex
    {
        Vertex();
        Vertex(const glm::vec3 &position);
        Vertex(glm::vec3 &&position);
        Vertex(const glm::vec3 &position, const glm::vec3 &normal);
        Vertex(glm::vec3 &&position, glm::vec3 &&normal);
        Vertex(const glm::vec3 &position, const glm::vec2 &uv);
        Vertex(glm::vec3 &&position, glm::vec2 &&uv);
        Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& uv);
        Vertex(glm::vec3 &&position, glm::vec3 &&normal,  glm::vec2 &&uv);
        Vertex(float xPosition, float yPosition, float zPosition);
        Vertex(float xPosition, float yPosition, float zPosition, float xUV, float yUV);
        Vertex(float xPosition, float yPosition, float zPosition, float xNormal, float yNormal, float zNormal);
        Vertex(float xPosition, float yPosition, float zPosition, float xNormal, float yNormal, float zNormal, float xUV, float yUV);
        Vertex(std::initializer_list<GLfloat> values);
        Vertex(std::initializer_list<float> position, std::initializer_list<float> normals_or_uv);
        Vertex(std::initializer_list<float> position, std::initializer_list<float> normals, std::initializer_list<float> uv);

        Vertex(const Vertex& rhs);
        Vertex(Vertex &&rhs) noexcept;
        Vertex &operator=(const Vertex &rhs);
        Vertex &operator=(Vertex &&rhs) noexcept;
        ~Vertex();

        GLfloat* GetPointer();

        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };
}