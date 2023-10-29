#include "Engine/Objects/Transform.h"
#include "Engine/Tools/Log/Logger.h"
#include <iostream>
#include <iomanip>

namespace Engine::Objects
{
    glm::vec3 RotateVector(glm::quat q, glm::vec3 v)
    {
        glm::vec3 t = glm::cross(glm::vec3(q.x, q.y, q.z), v);
        t *= 2;
        return v + q.w * t + glm::cross(glm::vec3(q.x, q.y, q.z), t);
    }

    Transform::Transform()
        : position()
        , rotation(1.0f, 0.0f, 0.0f, 0.0f)
        , scale(1.0f)
        , mainMatrix()
        , positionMatrix()
        , rotationMatrix()
        , scaleMatrix()
        , forward()
        , up()
        , right()
        , mainMatrixIsUpdated(false)
        , positionMatrixIsUpdated(false)
        , rotationMatrixIsUpdated(false)
        , scaleMatrixIsUpdated(false)
        , forwardIsUpdated(false)
        , upIsUpdated(false)
        , rightIsUpdated(false)
    {};

    Transform::Transform(glm::vec3 position)
        : Transform(position, glm::quat(), glm::vec3(1.0f))
    {};

    Transform::Transform(glm::quat rotation)
        : Transform(glm::vec3(0.0f), rotation, glm::vec3(1.0f))
    {};

    Transform::Transform(glm::vec3 position, glm::quat rotation)
        : Transform(position, rotation, glm::vec3(1.0f))
    {};

    Transform::Transform(glm::vec3 position, glm::vec3 scale)
        : Transform(position, glm::quat(), scale)
    {};

    Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : Transform(position, glm::quat(rotation), scale)
    {};

    Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
        : position(position)
        , rotation(rotation)
        , scale(scale)
        , mainMatrix()
        , positionMatrix()
        , rotationMatrix()
        , scaleMatrix()
        , forward()
        , up()
        , right()
        , mainMatrixIsUpdated(false)
        , positionMatrixIsUpdated(false)
        , rotationMatrixIsUpdated(false)
        , scaleMatrixIsUpdated(false)
        , forwardIsUpdated(false)
        , upIsUpdated(false)
        , rightIsUpdated(false)
    {};

    Transform::Transform(const Transform &rhs)
        : position(rhs.position)
        , rotation(rhs.rotation)
        , scale(rhs.scale)
        , mainMatrix(rhs.mainMatrix)
        , positionMatrix(rhs.positionMatrix)
        , rotationMatrix(rhs.rotationMatrix)
        , scaleMatrix(rhs.scaleMatrix)
        , forward(rhs.forward)
        , up(rhs.up)
        , right(rhs.right)
        , mainMatrixIsUpdated(rhs.mainMatrixIsUpdated)
        , positionMatrixIsUpdated(rhs.positionMatrixIsUpdated)
        , rotationMatrixIsUpdated(rhs.rotationMatrixIsUpdated)
        , scaleMatrixIsUpdated(rhs.scaleMatrixIsUpdated)
        , forwardIsUpdated(rhs.forwardIsUpdated)
        , upIsUpdated(rhs.upIsUpdated)
        , rightIsUpdated(rhs.rightIsUpdated)
    {};

    Transform::Transform(Transform &&rhs) noexcept
        : position(std::move(rhs.position))
        , rotation(std::move(rhs.rotation))
        , scale(std::move(rhs.scale))
        , mainMatrix(std::move(rhs.mainMatrix))
        , positionMatrix(std::move(rhs.positionMatrix))
        , rotationMatrix(std::move(rhs.rotationMatrix))
        , scaleMatrix(std::move(rhs.scaleMatrix))

        , forward(std::move(rhs.forward))
        , up(std::move(rhs.up))
        , right(std::move(rhs.right))
        , mainMatrixIsUpdated(rhs.mainMatrixIsUpdated)
        , positionMatrixIsUpdated(rhs.positionMatrixIsUpdated)
        , rotationMatrixIsUpdated(rhs.rotationMatrixIsUpdated)
        , scaleMatrixIsUpdated(rhs.scaleMatrixIsUpdated)
        , forwardIsUpdated(rhs.forwardIsUpdated)
        , upIsUpdated(rhs.upIsUpdated)
        , rightIsUpdated(rhs.rightIsUpdated)
    {};

    Transform &Transform::operator=(const Transform &rhs)
    {
        position = rhs.position;
        rotation = rhs.rotation;
        scale = rhs.scale;
        mainMatrix = rhs.mainMatrix;
        positionMatrix = rhs.positionMatrix;
        rotationMatrix = rhs.rotationMatrix;
        scaleMatrix = rhs.scaleMatrix;
        forward = rhs.forward;
        right = rhs.right;
        up = rhs.up;

        mainMatrixIsUpdated = rhs.mainMatrixIsUpdated;
        positionMatrixIsUpdated = rhs.positionMatrixIsUpdated;
        rotationMatrixIsUpdated = rhs.rotationMatrixIsUpdated;
        scaleMatrixIsUpdated = rhs.scaleMatrixIsUpdated;
        forwardIsUpdated = rhs.forwardIsUpdated;
        rightIsUpdated = rhs.rightIsUpdated;
        upIsUpdated = rhs.upIsUpdated;
        return *this;
    }

    Transform &Transform::operator=(Transform &&rhs) noexcept
    {
        position = std::move(rhs.position);
        rotation = std::move(rhs.rotation);
        scale = std::move(rhs.scale);
        mainMatrix = std::move(rhs.mainMatrix);
        positionMatrix = std::move(rhs.positionMatrix);
        rotationMatrix = std::move(rhs.rotationMatrix);
        scaleMatrix = std::move(rhs.scaleMatrix);
        forward = std::move(rhs.forward);
        right = std::move(rhs.right);
        up = std::move(rhs.up);
        mainMatrixIsUpdated = rhs.mainMatrixIsUpdated;
        positionMatrixIsUpdated = rhs.positionMatrixIsUpdated;
        rotationMatrixIsUpdated = rhs.rotationMatrixIsUpdated;
        scaleMatrixIsUpdated = rhs.scaleMatrixIsUpdated;
        forwardIsUpdated = rhs.forwardIsUpdated;
        rightIsUpdated = rhs.rightIsUpdated;
        upIsUpdated = rhs.upIsUpdated;

        return *this;
    }

    Transform::~Transform() {}

    void Transform::SetPosition(const glm::vec3 &value)
    {
        position = value;
        mainMatrixIsUpdated = false;
        positionMatrixIsUpdated = false;
    }

    void Transform::SetPosition(float x, float y, float z)
    {
        SetPosition(glm::vec3(x, y, z));
    }

    void Transform::SetPositionInOrientation(const glm::vec3 &value)
    {
        position = rotation * value;
        mainMatrixIsUpdated = false;
        positionMatrixIsUpdated = false;
    }

    void Transform::SetPositionInOrientation(float x, float y, float z)
    {
        SetPositionInOrientation(glm::vec3(x, y, z));
    }

    void Transform::Move(const glm::vec3 &delta)
    {
        position += RotateVector(rotation, delta);
        mainMatrixIsUpdated = false;
        positionMatrixIsUpdated = false;
    }

    void Transform::Move(float x, float y, float z)
    {
        Move(glm::vec3(x, y, z));
    }

    void Transform::MoveInOrientation(const glm::vec3 &delta)
    {
        position += rotation * delta;
        mainMatrixIsUpdated = false;
        positionMatrixIsUpdated = false;
    }

    void Transform::MoveInOrientation(float x, float y, float z)
    {
        MoveInOrientation(glm::vec3(x, y, z));
    }

    void Transform::SetRotation(const glm::quat &value)
    {
        rotation = glm::normalize(value);
        ClearDirectionUpdatedFlags();
        mainMatrixIsUpdated = false;
        rotationMatrixIsUpdated = false;
    }

    void Transform::SetRotation(const glm::vec3 &euler)
    {
        SetRotation(glm::quat(euler));
    }

    void Transform::SetRotation(float xEuler, float yEuler, float zEuler)
    {
        SetRotation(glm::vec3(xEuler, yEuler, zEuler));
    }

    void Transform::SetRotation(float radians, const glm::vec3 &axis)
    {
        SetRotation(glm::angleAxis(radians, axis));
    }

    void Transform::SetRotationInDegrees(const glm::vec3 &euler)
    {
        SetRotation(glm::radians(euler));
    }

    void Transform::SetRotationInDegrees(float xEuler, float yEuler, float zEuler)
    {
        SetRotation(glm::radians(xEuler), glm::radians(yEuler), glm::radians(zEuler));
    }

    void Transform::SetRotationInDegrees(float degrees, const glm::vec3 &axis)
    {
        SetRotation(glm::radians(degrees), axis);
    }

    void Transform::Rotate(const glm::quat &delta)
    {
        rotation = glm::normalize(glm::normalize(delta) * rotation);
        ClearDirectionUpdatedFlags();
        mainMatrixIsUpdated = false;
        rotationMatrixIsUpdated = false;
    }

    void Transform::Rotate(const glm::vec3 &euler)
    {
        Rotate(glm::quat(euler));
    }

    void Transform::Rotate(float xEuler, float yEuler, float zEuler)
    {
        Rotate(glm::vec3(xEuler, yEuler, zEuler));
    }

    void Transform::Rotate(float radians, const glm::vec3 &axis)
    {
        Rotate(glm::angleAxis(radians, axis));
    }

    void Transform::RotateInDegrees(const glm::vec3 &euler)
    {
        Rotate(glm::radians(euler));
    }

    void Transform::RotateInDegrees(float xEuler, float yEuler, float zEuler)
    {
        Rotate(glm::radians(xEuler), glm::radians(yEuler), glm::radians(zEuler));
    }

    void Transform::RotateInDegrees(float degrees, const glm::vec3 &axis)
    {
        Rotate(glm::radians(degrees), axis);
    }

    void Transform::RotateInOrientation(glm::vec3 value)
    {
        if (value.z != 0)
        {
            glm::quat roll = glm::normalize(glm::angleAxis(value.z, GetForwardDirection()));
            rotation = glm::normalize(std::move(roll) * rotation);
        }
        if (value.y != 0)
        {
            glm::quat yaw = glm::normalize(glm::angleAxis(value.y, GetUpDirection()));
            rotation = glm::normalize(std::move(yaw) * rotation);
        }
        if (value.x != 0)
        {
            glm::quat pitch = glm::normalize(glm::angleAxis(value.x, GetRightDirection()));
            rotation = glm::normalize(std::move(pitch) * rotation);
        }

        ClearDirectionUpdatedFlags();
        mainMatrixIsUpdated = false;
        rotationMatrixIsUpdated = false;
    }

    void Transform::RotateInOrientation(float x, float y, float z)
    {
        RotateInOrientation(glm::vec3(x, y, z));
    }

    void Transform::SetScale(const glm::vec3 &value)
    {
        scale = value;
        mainMatrixIsUpdated = false;
        scaleMatrixIsUpdated = false;
    }

    void Transform::SetScale(float x, float y, float z)
    {
        SetScale(glm::vec3(x, y, z));
    }

    void Transform::Scale(const glm::vec3 &value)
    {
        scale += value;
        mainMatrixIsUpdated = false;
        scaleMatrixIsUpdated = false;
    }

    void Transform::Scale(float x, float y, float z)
    {
        Scale(glm::vec3(x, y, z));
    }

    const glm::mat4 &Transform::GetTransformMatrix()
    {
        if (!mainMatrixIsUpdated)
        {
            mainMatrix = GetPositionMatrix() * GetRotationMatrix() * GetScaleMatrix();
            mainMatrixIsUpdated = true;
        }

        return mainMatrix;
    }

    const glm::mat4 &Transform::GetPositionMatrix()
    {
        if (!positionMatrixIsUpdated)
        {
            positionMatrix = glm::translate(glm::mat4(1.0f), position);
            positionMatrixIsUpdated = true;
        }
        return positionMatrix;
    }

    const glm::mat4 &Transform::GetRotationMatrix()
    {
        if (!rotationMatrixIsUpdated)
        {
            rotationMatrix = glm::mat4_cast(rotation);
            rotationMatrixIsUpdated = true;
        }
        return rotationMatrix;
    }

    const glm::mat4 &Transform::GetScaleMatrix()
    {
        if (!scaleMatrixIsUpdated)
        {
            scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
            scaleMatrixIsUpdated = true;
        }
        return scaleMatrix;
    }

    glm::vec3 Transform::GetForwardDirection()
    {
        if (!forwardIsUpdated)
        {
            forward = GetRotationMatrix()[2];
            forwardIsUpdated = true;
        }
        return forward;
    }

    glm::vec3 Transform::GetUpDirection()
    {
        if (!upIsUpdated)
        {
            up = GetRotationMatrix()[1];
            upIsUpdated = true;
        }
        return up;
    }

    glm::vec3 Transform::GetRightDirection()
    {
        if (!rightIsUpdated)
        {
            right = GetRotationMatrix()[0];
            rightIsUpdated = true;
        }
        return right;
    }

    void Transform::ClearDirectionUpdatedFlags()
    {
        forwardIsUpdated = false;
        upIsUpdated = false;
        rightIsUpdated = false;
    }

    Transform::operator std::string() const
    {
        std::ostringstream oss;
        glm::vec3 rotation = GetRotationInDegrees();
        oss << std::fixed << std::showpoint << std::setprecision(2);
        oss << "Transform {P:" << position << " "
            << "R:" << rotation << " "
            << "S:" << scale << "}" << std::defaultfloat << std::setprecision(std::cout.precision());
        return oss.str();
    }
}