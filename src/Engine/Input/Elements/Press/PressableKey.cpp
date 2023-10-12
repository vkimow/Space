#include "Engine/Input/Elements/Press/PressableKey.h"

namespace Engine::Input
{
	PressableKey::PressableKey(int key)
		: key(key)
	{}

	int PressableKey::GetKeyCode() const
	{
		return key;
	}

	PressableKey::~PressableKey()
	{}
}