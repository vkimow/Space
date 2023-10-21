#include "Engine/Input/Elements/Vector/Vector.h"
#include <iostream>

namespace Engine::Input
{
    Vector::Vector()
        : Vector(0.05f)
    {}

    Vector::Vector(float threshold)
        : isZero(true)
        , vector(0.0f, 0.0f)
        , threshold(threshold)
        , deltaX(nullptr)
        , deltaY(nullptr)
        , OnVectorChange()
    {}

    Vector::Vector(Vector && rhs) noexcept
        : isZero(rhs.isZero)
        , vector(std::move(rhs.vector))
        , threshold(rhs.threshold)
        , deltaX(rhs.deltaX)
        , deltaY(rhs.deltaY)
        , OnVectorChange(std::move(rhs.OnVectorChange))
    {
        rhs.deltaX = nullptr;
        rhs.deltaY = nullptr;
    }

    Vector &Vector::operator=(Vector &&rhs) noexcept
    {
        isZero = rhs.isZero;
        vector = std::move(rhs.vector);
        threshold = rhs.threshold;
        deltaX = rhs.deltaX;
        deltaY = rhs.deltaY;
        OnVectorChange = std::move(rhs.OnVectorChange);
        rhs.deltaX = nullptr;
        rhs.deltaY = nullptr;
        return *this;
    }

    Vector::~Vector()
    {
        if (deltaX)
        {
            delete deltaX;
            deltaX = nullptr;
        }

        if (deltaY)
        {
            delete deltaY;
            deltaY = nullptr;
        }
    }

    void Vector::ChangeVector(float x, float y)
    {
        ChangeVector(glm::vec2(x, y));
    }

    void Vector::ChangeVector(glm::vec2 value)
    {
        if (abs(value.x) < threshold)
        {
            value.x = 0.0f;
        }

        if (abs(value.y) < threshold)
        {
            value.y = 0.0f;
        }

        if (value == vector)
            return;

        if (deltaX && value.x != vector.x)
        {
            deltaX->ChangeDelta(value.x);
        }
        if (deltaY && value.y != vector.y)
        {
            deltaY->ChangeDelta(value.y);
        }

        isZero = value.y == 0.0f && value.x == 0.0f;
        vector = value;
        OnVectorChange(value);
    }

    void Vector::ChangeX(float value)
    {
        if (abs(value) < threshold)
        {
            value = 0.0f;
        }

        if (value == vector.x)
            return;

        if (deltaX)
        {
            deltaX->ChangeDelta(value);
        }

        isZero = value == 0 && vector.y == 0;
        vector.x = value;
        OnVectorChange(vector);
    }

    void Vector::ChangeY(float value)
    {
        if (abs(value) < threshold)
        {
            value = 0.0f;
        } 

        if (value == vector.y)
            return;

        if (deltaY)
        {
            deltaY->ChangeDelta(value);
        }

        isZero = vector.x == 0 && value == 0;
        vector.y = value;
        OnVectorChange(vector);
    }

    Delta * const Vector::GetDeltaX()
    {
        if (!deltaX)
        {
            deltaX = new Delta(0.0f);
        }
        return deltaX;
    }

    Delta *const Vector::GetDeltaY()
    {
        if (!deltaY)
        {
            deltaY = new Delta(0.0f);
        }
        return deltaY;
    }
}