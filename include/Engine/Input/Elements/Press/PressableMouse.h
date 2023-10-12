#pragma once

#include "Engine/Input/Elements/Press/Pressable.h"

namespace Engine::Input
{

    class  PressableMouse final: public Pressable
    {
        friend class InputModule;
        friend class Scheme;

    public:
        PressableMouse() = delete;
        PressableMouse(PressableMouse &&inputKeyElement) = delete;
        PressableMouse(const PressableMouse &inputKeyElement) = delete;
        ~PressableMouse();

    private:
        PressableMouse(int button);

    public:

        int GetButtonCode() const;

    private:
        const int button;
    };

}