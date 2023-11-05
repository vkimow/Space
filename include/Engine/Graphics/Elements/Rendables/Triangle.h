#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <initializer_list>

namespace Engine::Graphics
{
    struct Triangle
    {
        Triangle();

        Triangle(const glm::vec<3, GLuint> &indices);
        Triangle(glm::vec<3, GLuint> &&indices);
        Triangle(GLuint first, GLuint second, GLuint third);
        Triangle(std::initializer_list<GLuint> indices);

        Triangle(const Triangle &rhs);
        Triangle(Triangle &&rhs) noexcept;
        Triangle &operator=(const Triangle &rhs);
        Triangle &operator=(Triangle &&rhs) noexcept;
        ~Triangle();

        GLuint *GetPointer();

        inline GLuint Get(size_t index) const;
        inline GLuint &Get(size_t index);
        GLuint operator[](unsigned short int index) const;
        GLuint &operator[](unsigned short int index);

        glm::vec<3, GLuint> indices;
    };
}