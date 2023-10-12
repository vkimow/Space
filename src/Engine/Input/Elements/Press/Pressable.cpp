#include "Engine/Input/Elements/Press/Pressable.h"

namespace Engine::Input
{

	Pressable::Pressable()
		: isPressed(false)
	{}

	Pressable::~Pressable()
	{}

	void Pressable::Press()
	{
		isPressed = true;
		OnPress();
	}

	void Pressable::Release()
	{
		isPressed = false;
		OnRelease();
	}
}