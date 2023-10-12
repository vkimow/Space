 
#include "Engine/Input/Elements/Delta/Delta.h"

namespace Engine::Input
{
	Delta::Delta()
		: Delta(0.05f)
	{}

	Delta::Delta(float threshold)
		: isZero(true)
		, delta(0)
		, threshold(threshold)
	{}

	Delta::~Delta()
	{}


	void Delta::ChangeDelta(float value)
	{
		if (abs(value) < threshold)
		{
			value = 0.0f;
		}
		isZero = value == 0.0f;
		delta = value;
		OnDeltaChange(value);
	}
}