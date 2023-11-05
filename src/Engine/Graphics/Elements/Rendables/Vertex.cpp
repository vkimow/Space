#include "Engine/Graphics/Elements/Rendables/Vertex.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Tools/Log/Logger.h"

namespace Engine::Graphics
{
    Vertex::Vertex()
        : position(0.0f)
        , normal(0.0f)
        , uv(0.0f)
    {}

    Vertex::Vertex(const glm::vec3 &position)
        : Vertex(position, glm::vec3(), glm::vec2())
    {}

    Vertex::Vertex(glm::vec3 &&position)
        : Vertex(std::move(position), glm::vec3(), glm::vec2())
    {}

    Vertex::Vertex(const glm::vec3 &position, const glm::vec3 &normal)
        : position(position)
        , normal(normal)
    {}
    
    Vertex::Vertex(glm::vec3 &&position, glm::vec3 &&normal)
        : position(std::move(position))
        , normal(std::move(normal))
        , uv()
    {}
    
    Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &uv)
        : position(position)
        , normal()
        , uv(uv)
    {}
    
    Vertex::Vertex(glm::vec3 &&position, glm::vec2 &&uv)
        : position(std::move(position))
        , normal()
        , uv(std::move(uv))
    {}

    Vertex::Vertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &uv)
        : position(position)
        , normal(normal)
        , uv(uv)
    {}

    Vertex::Vertex(glm::vec3 &&position, glm::vec3 &&normal, glm::vec2 &&uv)
        : position(std::move(position))
        , normal(std::move(normal))
        , uv(std::move(uv))
    {}

    Vertex::Vertex(float xPosition, float yPosition, float zPosition)
        : Vertex(xPosition, yPosition, zPosition, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
    {}

    Vertex::Vertex(float xPosition, float yPosition, float zPosition, float xUV, float yUV)
        : Vertex(xPosition, yPosition, zPosition, 0.0f, 0.0f, 0.0f, xUV, yUV)
    {}
    
    Vertex::Vertex(float xPosition, float yPosition, float zPosition, float xNormal, float yNormal, float zNormal)
        : Vertex(xPosition, yPosition, zPosition, xNormal, yNormal, zNormal, 0.0f, 0.0f)
    {}
    
    Vertex::Vertex(float xPosition, float yPosition, float zPosition, float xNormal, float yNormal, float zNormal, float xUV, float yUV)
        : position(xPosition, yPosition, zPosition)
        , normal(xNormal, yNormal, zNormal)
        , uv(xUV, yUV)
    {}

    Vertex::Vertex(std::initializer_list<GLfloat> values)
        : position()
        , normal()
        , uv()
    {
        if (!(values.size() == 3 || values.size() == 5 || values.size() == 6 || values.size() == 8))
        {
            LOG_ERROR("Initializer List should be include 3 (position) or 5 (position + uvs) or 6 (position + normals) or 8 (position + normal + uv) values");
        }

        auto it = values.begin();
        if (values.size() > 2)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                position[i] = *it;
                ++it;
            }
        }

        if (values.size() > 5)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                normal[i] = *it;
                ++it;
            }
        }
        else if (values.size() == 5)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                uv[i] = *it;
                ++it;
            }
        }

        if (values.size() > 7)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                uv[i] = *it;
                ++it;
            }
        }
    }

    Vertex::Vertex(std::initializer_list<float> position, std::initializer_list<float> normals_or_uv)
        : position()
        , normal()
        , uv()
    {
        if (position.size() == 3)
        {
            auto it = position.begin();
            for (size_t i = 0; i < 3; ++i)
            {
                this->position[i] = *it;
                ++it;
            }
        }
        else
        {
            LOG_ERROR("Initializer List for position should be include 3 values");
        }

        switch (normals_or_uv.size())
        {
            case 2:
            {
                auto it = normals_or_uv.begin();
                for (size_t i = 0; i < 2; ++i)
                {
                    this->uv[i] = *it;
                    ++it;
                }
                break;
            }
            case 3:
            {
                auto it = normals_or_uv.begin();
                for (size_t i = 0; i < 3; ++i)
                {
                    this->normal[i] = *it;
                    ++it;
                }
                break;
            }
            default:
            {
                LOG_ERROR("Initializer List for uv or normals should be include 2 or 3 values");
            }
        }
    }

    Vertex::Vertex(std::initializer_list<float> position, std::initializer_list<float> normal, std::initializer_list<float> uv)
        : position()
        , normal()
        , uv()
    {
        if (position.size() == 3)
        {
            auto it = position.begin();
            for (size_t i = 0; i < 3; ++i)
            {
                this->position[i] = *it;
                ++it;
            }
        }
        else
        {
            LOG_ERROR("Initializer List for position should be include 3 values");
        }

        if (normal.size() == 3)
        {
            auto it = normal.begin();
            for (size_t i = 0; i < 3; ++i)
            {
                this->normal[i] = *it;
                ++it;
            }
        }
        else
        {
            LOG_ERROR("Initializer List for normal should be include 3 values");
        }

        if (uv.size() == 2)
        {
            auto it = uv.begin();
            for (size_t i = 0; i < 2; ++i)
            {
                this->uv[i] = *it;
                ++it;
            }
        }
        else
        {
            LOG_ERROR("Initializer List for uv should be include 2 values");
        }
    }


    Vertex::Vertex(const Vertex &rhs)
        : position(rhs.position)
        , normal(rhs.normal)
        , uv(rhs.uv)
    {}

    Vertex::Vertex(Vertex &&rhs) noexcept
        : position(std::move(rhs.position))
        , normal(std::move(rhs.normal))
        , uv(std::move(rhs.uv))
    {}

    Vertex &Vertex::operator=(const Vertex &rhs)
    {
        position = rhs.position;
        normal = rhs.normal;
        uv = rhs.uv;
        return *this;
    }

    Vertex &Vertex::operator=(Vertex &&rhs) noexcept
    {
        position = std::move(rhs.position);
        normal = std::move(rhs.normal);
        uv = std::move(rhs.uv);
        return *this;
    }
    
    GLfloat *Vertex::GetPointer()
    {
        return glm::value_ptr(position);
    }

    Vertex::~Vertex()
    {}
}