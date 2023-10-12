#include "Engine/Input/Elements/Press/PressableMouse.h"

namespace Engine::Input
{
	PressableMouse::PressableMouse(int button)
		: button(button)
	{}

	PressableMouse::~PressableMouse() {}

	int PressableMouse::GetButtonCode() const
	{
		return button;
	}
}