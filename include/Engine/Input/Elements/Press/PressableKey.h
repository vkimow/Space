#pragma once

#include "Engine/Input/Elements/Press/Pressable.h"
#include <memory>

namespace Engine::Input
{
    class  PressableKey final: public Pressable
    {
        friend class InputModule;
        friend class Scheme;

    private:
        PressableKey() = delete;
        PressableKey(const PressableKey &rhs) = delete;
        PressableKey(PressableKey &&rhs) = delete;
        PressableKey &operator=(const PressableKey &rhs) = delete;
        PressableKey &operator=(PressableKey &&rhs) = delete;

        PressableKey(int key);
        ~PressableKey();

    public:
        int GetKeyCode() const;

    private:
        const int key;
    };

}