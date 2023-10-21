#pragma once

#include "Engine/Input/Elements/Press/Pressable.h"

namespace Engine::Input
{

    class  PressableMouse final: public Pressable
    {
        friend class InputModule;
        friend class Scheme;

    private:
        PressableMouse() = delete;
        PressableMouse(const PressableMouse &rhs) = delete;
        PressableMouse(PressableMouse &&rhs) = delete;
        PressableMouse &operator=(const PressableMouse &rhs) = delete;
        PressableMouse &operator=(PressableMouse &&rhs) = delete;

        PressableMouse(int button);
        ~PressableMouse();

    public:
        int GetButtonCode() const;

    private:
        const int button;
    };

}