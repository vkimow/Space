#include "Engine/Input/Elements/Delta/DeltaPressable.h"
#include "Engine/Input/Elements/Press/PressableKey.h"

namespace Engine::Input
{
    DeltaPressable::DeltaPressable(Pressable *const positive, Pressable *const negative, float threshold)
        : Delta(threshold)
        , positive(positive)
        , negative(negative)
        , updateFunction(this, &Engine::Input::DeltaPressable::Update)
    {
        SetCallbacks();
    }

    DeltaPressable::DeltaPressable(DeltaPressable &&rhs) noexcept
        : Delta(std::move(rhs))
        , positive(rhs.positive)
        , negative(rhs.negative)
        , updateFunction(this, &Engine::Input::DeltaPressable::Update)
    {
        SetCallbacks();
        rhs.RemoveCallbacks();
        rhs.positive = nullptr;
        rhs.negative = nullptr;
    }

    DeltaPressable &DeltaPressable::operator=(DeltaPressable &&rhs) noexcept
    {
        Delta::operator=(std::move(rhs));
        positive = rhs.positive;
        negative = rhs.negative;
        SetCallbacks();
        rhs.ClearCallbacks();
        return *this;
    }

    DeltaPressable::~DeltaPressable()
    {
        ClearCallbacks();
    }

    void DeltaPressable::SetCallbacks()
    {
        if (positive)
        {
            positive->AddListenerOnPress(updateFunction);
            positive->AddListenerOnRelease(updateFunction);
        }

        if (negative)
        {
            negative->AddListenerOnPress(updateFunction);
            negative->AddListenerOnRelease(updateFunction);
        }
    }

    void DeltaPressable::RemoveCallbacks()
    {
        if (positive)
        {
            positive->RemoveListenerOnPress(updateFunction);
            positive->RemoveListenerOnRelease(updateFunction);
        }

        if (negative)
        {
            negative->RemoveListenerOnPress(updateFunction);
            negative->RemoveListenerOnRelease(updateFunction);
        }
    }

    void DeltaPressable::ClearCallbacks()
    {
        RemoveCallbacks();
        positive = nullptr;
        negative = nullptr;
    }

    void DeltaPressable::Update()
    {
        int value = positive->IsPressed() - negative->IsPressed();
        ChangeDelta(static_cast<float>(value));
    }
}
