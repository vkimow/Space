#pragma once

#include "Engine/Input/Elements/Vector/Vector.h"
#include "Engine/Tools/Events/MemberFunction.h"
#include <memory>

namespace Engine::Input
{
	class Delta;

	class  VectorDelta final: public Vector
	{
        friend class InputModule;
        friend class Scheme;

	public:
		VectorDelta() = delete;
		VectorDelta(Delta* const x,
					Delta* const y);

        ~VectorDelta();

    private:
        void SetCallbacks();
        void RemoveCallbacks();
        void UpdateX(float value);
		void UpdateY(float value);

	private:
		Delta* const x;
		Delta* const y;
        Engine::Tools::Events::MemberFunction<VectorDelta, float> updateXFunction;
		Engine::Tools::Events::MemberFunction<VectorDelta, float> updateYFunction;
	};
}
