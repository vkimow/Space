#pragma once

#include "Engine/Input/Main/Element.h"
#include "Engine/Tools/Events/Action.h"

namespace Engine::Input
{
    class Delta: public Element
    {
        friend class InputModule;
        friend class Vector;
        friend class Scheme;

    protected:
        Delta();
        Delta(float threshold);

    public:
        Delta(const Delta &rhs) = delete;
        Delta(Delta &&rhs) noexcept;

        Delta &operator=(const Delta &rhs) = delete;
        Delta &operator=(Delta &&rhs) noexcept;

        virtual ~Delta();

    public:
        float IsZero() const { return isZero; }
        float GetDelta() const { return delta; }

    public:
        float GetThreshold() { return threshold; }
        void SetThreshold(float value) { threshold = value; }

    protected:
        void ChangeDelta(float value);

    private:
        CREATE_ACTION(float, OnDeltaChange);

    private:
        bool isZero;
        float delta;
        float threshold;
    };

}
