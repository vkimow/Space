#include "Engine/Input/Elements/Vector/VectorPressable.h"
#include "Engine/Input/Elements/Delta/DeltaPressable.h"
#include "Engine/Input/Elements/Press/Pressable.h"


namespace Engine::Input
{

    VectorPressable::VectorPressable(Pressable *const xPositive, Pressable *const xNegative, Pressable *const yPositive, Pressable *const yNegative)
        : Vector()
        , xPositive(xPositive)
        , xNegative(xNegative)
        , yPositive(yPositive)
        , yNegative(yNegative)
        , updateXFunction(this, &VectorPressable::UpdateX)
        , updateYFunction(this, &VectorPressable::UpdateY)
    {
        SetCallbacks();
    }

    VectorPressable::VectorPressable(DeltaPressable *const x, DeltaPressable *const y)
        : VectorPressable(x->positive, x->negative, y->positive, y->negative)
    {}

    VectorPressable::VectorPressable(VectorPressable &&rhs) noexcept
        : Vector(std::move(rhs))
        , xPositive(rhs.xPositive)
        , xNegative(rhs.xNegative)
        , yPositive(rhs.yPositive)
        , yNegative(rhs.yNegative)
        , updateXFunction(this, &VectorPressable::UpdateX)
        , updateYFunction(this, &VectorPressable::UpdateY)
    {
        SetCallbacks();
        rhs.ClearCallbacks();
    }

    VectorPressable &VectorPressable::operator=(VectorPressable &&rhs) noexcept
    {
        Vector::operator=(std::move(rhs));
        xPositive = rhs.xPositive;
        xNegative = rhs.xNegative;
        yPositive = rhs.yPositive;
        yNegative = rhs.yNegative;
        SetCallbacks();
        rhs.ClearCallbacks();
        return *this;
    }

    VectorPressable::~VectorPressable()
    {
        ClearCallbacks();
    };

    void VectorPressable::SetCallbacks()
    {
        if (xPositive)
        {
            xPositive->AddListenerOnPress(updateXFunction);
            xPositive->AddListenerOnRelease(updateXFunction);
        }

        if (xNegative)
        {
            xNegative->AddListenerOnPress(updateXFunction);
            xNegative->AddListenerOnRelease(updateXFunction);
        }

        if (yPositive)
        {
            yPositive->AddListenerOnPress(updateYFunction);
            yPositive->AddListenerOnRelease(updateYFunction);

        }

        if (yNegative)
        {
            yNegative->AddListenerOnPress(updateYFunction);
            yNegative->AddListenerOnRelease(updateYFunction);
        }
    }

    void VectorPressable::RemoveCallbacks()
    {
        if (xPositive)
        {
            xPositive->RemoveListenerOnPress(updateXFunction);
            xPositive->RemoveListenerOnRelease(updateXFunction);
        }

        if (xNegative)
        {
            xNegative->RemoveListenerOnPress(updateXFunction);
            xNegative->RemoveListenerOnRelease(updateXFunction);
        }

        if (yPositive)
        {
            yPositive->RemoveListenerOnPress(updateYFunction);
            yPositive->RemoveListenerOnRelease(updateYFunction);
        }

        if (yNegative)
        {
            yNegative->RemoveListenerOnPress(updateYFunction);
            yNegative->RemoveListenerOnRelease(updateYFunction);
        }
    }

    void VectorPressable::ClearCallbacks()
    {
        RemoveCallbacks();
        xPositive = nullptr;
        xNegative = nullptr;
        yPositive = nullptr;
        yNegative = nullptr;
    }

    void VectorPressable::UpdateX()
    {
        int x = xPositive->IsPressed() - xNegative->IsPressed();
        ChangeX(x);
    }

    void VectorPressable::UpdateY()
    {
        int y = yPositive->IsPressed() - yNegative->IsPressed();
        ChangeY(y);
    }
}