#include "Engine/Input/Elements\Vector/VectorDelta.h"
#include "Engine/Input/Elements\Delta\Delta.h"
#include <iostream>

namespace Engine::Input
{
	VectorDelta::VectorDelta(Delta *const x, Delta *const y)
		: x(x)
		, y(y)
		, updateXFunction(this, &VectorDelta::UpdateX)
		, updateYFunction(this, &VectorDelta::UpdateY)
	{
		SetCallbacks();
	}

	VectorDelta::~VectorDelta()
	{
		RemoveCallbacks();
	}

	void VectorDelta::SetCallbacks()
	{
		x->AddListenerOnDeltaChange(updateXFunction);
		y->AddListenerOnDeltaChange(updateYFunction);
	}

	void VectorDelta::RemoveCallbacks()
	{
		x->RemoveListenerOnDeltaChange(updateXFunction);
		y->RemoveListenerOnDeltaChange(updateYFunction);
	}

	void VectorDelta::UpdateX(float value)
	{
		ChangeX(value);
	}

	void VectorDelta::UpdateY(float value)
	{
		ChangeY(value);
	}
}