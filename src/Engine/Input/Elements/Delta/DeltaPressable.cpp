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

	DeltaPressable::~DeltaPressable()
	{
		RemoveCallbacks();
	}

	void DeltaPressable::SetCallbacks()
	{
		positive->AddListenerOnPress(updateFunction);
		positive->AddListenerOnRelease(updateFunction);
		negative->AddListenerOnPress(updateFunction);
		negative->AddListenerOnRelease(updateFunction);
	}

	void DeltaPressable::RemoveCallbacks()
	{
		positive->RemoveListenerOnPress(updateFunction);
		positive->RemoveListenerOnRelease(updateFunction);
		negative->RemoveListenerOnPress(updateFunction);
		negative->RemoveListenerOnRelease(updateFunction);
	}

	void DeltaPressable::Update()
	{
		int value = positive->IsPressed() - negative->IsPressed();
		ChangeDelta(static_cast<float>(value));
	}
}
