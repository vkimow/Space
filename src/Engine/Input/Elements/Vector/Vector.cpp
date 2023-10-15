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
    {}

    Vector::~Vector()
    {}

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

        isZero = vector.x == 0 && value == 0;
        vector.y = value;
        OnVectorChange(vector);
    }
}