#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include <unordered_map>
#include <string>
#include <sstream>

namespace Engine::Objects
{
    class Transform
    {
    public:
        Transform();
        Transform(glm::vec3 position);
        Transform(glm::vec3 position, glm::quat orientation);
        Transform(glm::vec3 position, glm::vec3 scale);
        Transform(glm::vec3 position, glm::quat orientation, glm::vec3 scale);
        Transform(const Transform &rhs);
        Transform(Transform &&rhs) noexcept;

        Transform &operator=(const Transform &rhs);
        Transform &operator=(Transform &&rhs) noexcept;

        ~Transform();

    public:
        template<typename... Args>
        void SetPosition(Args&&... args)
        {
            glm::vec3 vector(std::forward<Args>(args)...);
            position = std::move(vector);
        }

    public:
        template<typename... Args>
        void Move(Args&&... args)
        {
            glm::vec3 delta(std::forward<Args>(args)...);
            position += delta;
        }

    public:
        template<typename... Args>
        void SetOrientation(Args&&... args)
        {
            glm::quat quaternion(std::forward<Args>(args)...);
            orientation = glm::normalize(quaternion);
        }
        void SetOrientation(float x, float y, float z) { SetOrientation(glm::vec3(x, y, z)); }
        void SetOrientationInDegrees(float degrees, const glm::vec3 &axis) { SetOrientation(glm::radians(degrees), axis); }
        void SetOrientationInDegrees(const glm::vec3 &euler) { SetOrientation(glm::radians(euler)); }
        void SetOrientationInDegrees(float xEuler, float yEuler, float zEuler) { SetOrientationInDegrees(glm::vec3(xEuler, yEuler, zEuler)); }

    public:
        template<typename... Args>
        void Rotate(Args&&... args)
        {
            glm::quat delta(std::forward<Args>(args)...);
            orientation = glm::normalize(glm::normalize(delta) * orientation);
        }
        void Rotate(float x, float y, float z) { Rotate(glm::vec3(x, y, z)); }
        void RotateInDegrees(float degrees, const glm::vec3 &axis) { Rotate(glm::radians(degrees), axis); }
        void RotateInDegrees(const glm::vec3 &euler) { Rotate(glm::radians(euler)); }
        void RotateInDegrees(float xEuler, float yEuler, float zEuler) { SetOrientationInDegrees(glm::vec3(xEuler, yEuler, zEuler)); }

    public:
        template<typename... Args>
        void SetScale(Args&&... args)
        {
            glm::vec3 vector(std::forward<Args>(args)...);
            scale = std::move(vector);
        }

    public:
        template<typename... Args>
        void Scale(Args&&... args)
        {
            glm::vec3 delta(std::forward<Args>(args)...);
            scale += delta;
        }

    public:
        glm::vec3 GetPosition() const { return position; }
        glm::quat GetOrientation() const { return orientation; }
        glm::vec3 GetEurlerOrientation() const { return glm::eulerAngles(orientation); }
        glm::vec3 GetScale() const { return scale; }

    public:
        glm::mat4 GetTransformMatrix();

    private:
        glm::vec3 position;
        glm::quat orientation;
        glm::vec3 scale;

    public:
        operator std::string() const;
    };
}