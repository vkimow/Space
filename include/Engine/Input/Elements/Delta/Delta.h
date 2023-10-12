#pragma once

#include "Engine/Input/Main/Element.h"
#include "Engine/Tools/Events/Action.h"

namespace Engine::Input
{
    class Delta: public Element
    {
        friend class InputModule;
        friend class Scheme;

    protected:
        Delta();
        Delta(float threshold);

    public:
        virtual ~Delta();

    public:
        float IsZero() const { return isZero; }
        float GetDelta() const { return delta; }

    protected:
        void ChangeDelta(float value);

    private:
        CREATE_ACTION(float, OnDeltaChange)

    private:
        bool isZero;
        float delta;
        float threshold;
    };

}
