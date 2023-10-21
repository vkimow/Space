
#include "Engine/Input/Elements/Delta/Delta.h"

namespace Engine::Input
{
    Delta::Delta()
        : Delta(0.05f)
    {}

    Delta::Delta(float threshold)
        : isZero(true)
        , delta(0)
        , threshold(threshold)
        , OnDeltaChange()
    {}

    Delta::Delta(Delta &&rhs) noexcept
        : isZero(rhs.isZero)
        , delta(rhs.delta)
        , threshold(rhs.threshold)
        , OnDeltaChange(std::move(rhs.OnDeltaChange))
    {}

    Delta &Delta::operator=(Delta &&rhs) noexcept
    {
        isZero = rhs.isZero;
        delta = rhs.delta;
        threshold = rhs.threshold;
        OnDeltaChange = std::move(rhs.OnDeltaChange);
        return *this;
    }

    Delta::~Delta()
    {}

    void Delta::ChangeDelta(float value)
    {
        if (abs(value) < threshold)
        {
            value = 0.0f;
        }

        if (value == delta)
            return;

        isZero = value == 0.0f;
        delta = value;
        OnDeltaChange(value);
    }
}