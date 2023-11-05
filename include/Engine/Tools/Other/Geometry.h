#pragma once

#include <glm/glm.hpp>

namespace Engine::Tools::Geometry
{
    glm::vec3 RotateVector(const glm::quat &q, const glm::vec3 &v);
    float GetSqrLength(const glm::vec3 &v);
    glm::vec3 GetNormilized(const glm::vec3 &v);
    glm::vec3 GetNormilized(const glm::vec3 &v, float length);
    glm::vec3 GetNormilizedFromSqrLength(const glm::vec3 &v, float sqrLength);
}
