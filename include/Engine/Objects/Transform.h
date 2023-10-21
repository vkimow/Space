#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include <unordered_map>
#include <string>
#include <sstream>
#include <ostream>
#include <iostream>
#include <iomanip>

namespace Engine::Objects
{
    class Transform
    {
    public:
        Transform();
        Transform(glm::vec3 position);
        Transform(glm::quat rotation);
        Transform(glm::vec3 position, glm::quat rotation);
        Transform(glm::vec3 position, glm::vec3 scale);
        Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
        Transform(const Transform &rhs);
        Transform(Transform &&rhs) noexcept;

        Transform &operator=(const Transform &rhs);
        Transform &operator=(Transform &&rhs) noexcept;

        ~Transform();

    public:
        void SetPosition(const glm::vec3 &value);
        void SetPosition(float x, float y, float z);
        void SetPositionInOrientation(const glm::vec3 &value);
        void SetPositionInOrientation(float x, float y, float z);

    public:
        void Move(const glm::vec3 &delta);
        void Move(float x, float y, float z);
        void MoveInOrientation(const glm::vec3 &delta);
        void MoveInOrientation(float x, float y, float z);

    public:
        void SetRotation(const glm::quat &value);
        void SetRotation(const glm::vec3 &euler);
        void SetRotation(float xEuler, float yEuler, float zEuler);
        void SetRotation(float radians, const glm::vec3 &axis);
        void SetRotationInDegrees(const glm::vec3 &euler);
        void SetRotationInDegrees(float xEuler, float yEuler, float zEuler);
        void SetRotationInDegrees(float degrees, const glm::vec3 &axis);

    public:
        void Rotate(const glm::quat &delta);
        void Rotate(const glm::vec3 &euler);
        void Rotate(float xEuler, float yEuler, float zEuler);
        void Rotate(float radians, const glm::vec3 &axis);
        void RotateInDegrees(const glm::vec3 &euler);
        void RotateInDegrees(float xEuler, float yEuler, float zEuler);
        void RotateInDegrees(float degrees, const glm::vec3 &axis);
        void RotateInOrientation(glm::vec3 delta);
        void RotateInOrientation(float x, float y, float z);

    public:
        void SetScale(const glm::vec3 &value);
        void SetScale(float x, float y, float z);

    public:
        void Scale(const glm::vec3 &value);
        void Scale(float x, float y, float z);

    public:
        glm::vec3 GetPosition() const { return position; }
        glm::quat GetRotation() const { return rotation; }
        glm::vec3 GetRotationInRadians() const { return glm::eulerAngles(rotation); }
        glm::vec3 GetRotationInDegrees() const { return glm::degrees(GetRotationInRadians()); }
        glm::vec3 GetScale() const { return scale; }

    public:
        const glm::mat4& GetTransformMatrix();
        const glm::mat4& GetRotationMatrix();
        const glm::mat4& GetScaleMatrix();
        const glm::mat4& GetPositionMatrix();


    private:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
        glm::mat4 positionMatrix;
        glm::mat4 rotationMatrix;
        glm::mat4 scaleMatrix;
        glm::mat4 mainMatrix;
        bool positionMatrixIsUpdated;
        bool rotationMatrixIsUpdated;
        bool scaleMatrixIsUpdated;
        bool mainMatrixIsUpdated;

    public:
        glm::vec3 GetForwardDirection();
        glm::vec3 GetUpDirection();
        glm::vec3 GetRightDirection();
        void ClearDirectionUpdatedFlags();

    private:
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 right;
        bool forwardIsUpdated;
        bool upIsUpdated;
        bool rightIsUpdated;

    public:
        operator std::string() const;
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const glm::vec<3, T> &vector)
    {
        os << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
        return os;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const glm::vec<2, T> &vector)
    {
        os << "(" << vector.x << "," << vector.y << ")";
        return os;
    }
}