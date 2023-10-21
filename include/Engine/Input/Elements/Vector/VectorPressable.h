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
            Pressable *const yNegative);

        VectorPressable(DeltaPressable *const x,
            DeltaPressable *const y);

        VectorPressable(const VectorPressable &rhs) = delete;
        VectorPressable(VectorPressable &&rhs) noexcept;

        VectorPressable &operator=(const VectorPressable &rhs) = delete;
        VectorPressable &operator=(VectorPressable &&rhs) noexcept;

        ~VectorPressable();

    private:
        void SetCallbacks();
        void RemoveCallbacks();
        void ClearCallbacks();
        void UpdateX();
        void UpdateY();

    private:
        Pressable *xPositive;
        Pressable *xNegative;
        Pressable *yPositive;
        Pressable *yNegative;
        ::Engine::Tools::Events::MemberFunction<VectorPressable, void> updateXFunction;
        ::Engine::Tools::Events::MemberFunction<VectorPressable, void> updateYFunction;
    };
}