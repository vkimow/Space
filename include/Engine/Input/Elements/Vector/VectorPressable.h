#pragma once

#include "Engine/Input/Elements/Vector/Vector.h"
#include "Engine/Tools/Events/MemberFunction.h"

namespace Engine::Input
{
    class Pressable;
    class DeltaPressable;

    class  VectorPressable final: public Vector
    {
        friend class InputModule;
        friend class Scheme;

    public:
        VectorPressable() = delete;
        VectorPressable(Pressable *const xPositive,
            Pressable *const xNegative,
            Pressable *const yPositive,
            Pressable *const yNegative,
            float threshold = 0.05f);

        VectorPressable(DeltaPressable *const x,
            DeltaPressable *const y,
            float threshold = 0.05f);

        ~VectorPressable();

    private:
        void SetCallbacks();
        void RemoveCallbacks();
        void UpdateX();
        void UpdateY();

    private:
        Pressable *const xPositive;
        Pressable *const xNegative;
        Pressable *const yPositive;
        Pressable *const yNegative;
        Engine::Tools::Events::MemberFunction<VectorPressable, void> updateXFunction;
        Engine::Tools::Events::MemberFunction<VectorPressable, void> updateYFunction;
    };
}