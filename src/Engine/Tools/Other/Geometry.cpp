#include "Engine/Tools/Other/Geometry.h"
#include <glm/gtc/quaternion.hpp>

namespace Engine::Tools::Geometry
{
    glm::vec3 RotateVector(const glm::quat &q, const glm::vec3 &v)
    {
        glm::vec3 t = glm::cross(glm::vec3(q.x, q.y, q.z), v);
        t *= 2;
        return v + q.w * t + glm::cross(glm::vec3(q.x, q.y, q.z), t);
    }

    float GetSqrLength(const glm::vec3 &v)
    {
        return glm::dot(v, v);
    }

    glm::vec3 GetNormilized(const glm::vec3 &v)
    {
        return glm::normalize(v);
    }

    glm::vec3 GetNormilized(const glm::vec3 &v, float length)
    {
        return glm::vec3(v.x / length, v.y / length, v.z / length);
    }

    glm::vec3 GetNormilizedFromSqrLength(const glm::vec3 &v, float sqrLength)
    {
        float length = glm::sqrt(sqrLength);
        return GetNormilized(v, std::move(length));
    }
}
