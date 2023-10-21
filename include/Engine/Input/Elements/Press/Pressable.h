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

    public:
        Pressable(const Pressable &rhs) = delete;
        Pressable(Pressable &&rhs) = delete;
        Pressable &operator=(const Pressable &rhs) = delete;
        Pressable &operator=(Pressable &&rhs) = delete;

        ~Pressable();

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