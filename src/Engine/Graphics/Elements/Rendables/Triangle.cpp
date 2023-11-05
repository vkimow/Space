#include "Engine/Graphics/Elements/Rendables/Triangle.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    Triangle::Triangle()
        : indices()
    {}

    Triangle::Triangle(const glm::vec<3, GLuint>&indices)
        : indices(indices)
    {}

    Triangle::Triangle(glm::vec<3, GLuint> && indices)
        : indices(std::move(indices))
    {}

    Triangle::Triangle(GLuint first, GLuint second, GLuint third)
        : indices(first, second, third)
    {}

    Triangle::Triangle(std::initializer_list<GLuint> indices)
        : indices()
    {
        if (indices.size() == 3)
        {
            auto it = indices.begin();
            for (size_t i = 0; i < 3; ++i)
            {
                this->indices[i] = *it;
                ++it;
            }
        }
        else
        {
            LOG_ERROR("Initializer List for indices should be include 3 values");
        }
    }


    Triangle::Triangle(const Triangle & rhs)
        : indices(rhs.indices)
    {}

    Triangle::Triangle(Triangle && rhs) noexcept
        : indices(std::move(rhs.indices))
    {}

    Triangle &Triangle::operator=(const Triangle & rhs)
    {
        indices = rhs.indices;
        return *this;
    }

    Triangle &Triangle::operator=(Triangle &&rhs) noexcept
    {
        indices = std::move(rhs.indices);
        return *this;
    }

    GLuint *Triangle::GetPointer()
    {
        return glm::value_ptr(indices);
    }

    GLuint Triangle::Get(size_t index) const
    {
        if (index < 0 && index > 2)
        {
            LOG_ERROR("Triangle only have 3 indices. Out of bound");
        }

        return indices[index];
    }

    GLuint &Triangle::Get(size_t index)
    {
        if (index < 0 && index > 2)
        {
            LOG_ERROR("Triangle only have 3 indices. Out of bound");
        }

        return indices[index];
    }

    GLuint Triangle::operator[](unsigned short int index) const
    {
        return Get(index);
    }

    GLuint &Triangle::operator[](unsigned short int index)
    {
        return Get(index);
    }

    Triangle::~Triangle()
    {}
}