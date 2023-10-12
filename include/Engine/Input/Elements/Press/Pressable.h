#pragma once

#include "Engine/Input/Main/Element.h"
#include "Engine/Tools/Events/Action.h"

namespace Engine::Input
{
    class  Pressable: public Element
    {
        friend class InputModule;
        friend class Scheme;

    protected:
        Pressable();
        virtual ~Pressable() override;

    public:

    public:
        bool IsPressed() const { return isPressed; }

    private:
        void Press();
        void Release();

    public:
        CREATE_ACTION(void, OnPress);
        CREATE_ACTION(void, OnRelease);

    private:
        bool isPressed;
    };
}