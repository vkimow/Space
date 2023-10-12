#include "Engine/Input/Elements/Vector/VectorPressable.h"
#include "Engine/Input/Elements/Delta/DeltaPressable.h"
#include "Engine/Input/Elements/Press/Pressable.h"


namespace Engine::Input
{

    VectorPressable::VectorPressable(Pressable *const xPositive, Pressable *const xNegative, Pressable *const yPositive, Pressable *const yNegative, float threshold)
        : Vector(threshold)
        , xPositive(xPositive)
        , xNegative(xNegative)
        , yPositive(yPositive)
        , yNegative(yNegative)
        , updateXFunction(this, &VectorPressable::UpdateX)
        , updateYFunction(this, &VectorPressable::UpdateY)
    {
        SetCallbacks();
    }

    VectorPressable::VectorPressable(DeltaPressable *const x, DeltaPressable *const y, float threshold)
        : VectorPressable(x->positive, x->negative, y->positive, y->negative, threshold)
    {}

    VectorPressable::~VectorPressable()
    {
        RemoveCallbacks();
    };

    void VectorPressable::SetCallbacks()
    {
        xPositive->AddListenerOnPress(updateXFunction);
        xNegative->AddListenerOnPress(updateXFunction);
        xPositive->AddListenerOnRelease(updateXFunction);
        xNegative->AddListenerOnRelease(updateXFunction);

        yPositive->AddListenerOnPress(updateYFunction);
        yNegative->AddListenerOnPress(updateYFunction);
        yPositive->AddListenerOnRelease(updateYFunction);
        yNegative->AddListenerOnRelease(updateYFunction);
    }

    void VectorPressable::RemoveCallbacks()
    {
        xPositive->RemoveListenerOnPress(updateXFunction);
        xNegative->RemoveListenerOnPress(updateXFunction);
        xPositive->RemoveListenerOnRelease(updateXFunction);
        xNegative->RemoveListenerOnRelease(updateXFunction);

        yPositive->RemoveListenerOnPress(updateYFunction);
        yNegative->RemoveListenerOnPress(updateYFunction);
        yPositive->RemoveListenerOnRelease(updateYFunction);
        yNegative->RemoveListenerOnRelease(updateYFunction);
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