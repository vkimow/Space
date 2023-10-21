#pragma once

#include "Delta.h"
#include "Engine/Tools/Events/MemberFunction.h"
#include <memory>

namespace Engine::Input
{
	class  Pressable;

	class  DeltaPressable final: public Delta
	{
		friend class InputModule;
		friend class Scheme;
		friend class VectorPressable;

	protected:
		DeltaPressable() = delete;
		DeltaPressable(Pressable *const positive, Pressable *const negative, float threshold = 0.05f);

	public:
		DeltaPressable(const DeltaPressable &rhs) = delete;
		DeltaPressable(DeltaPressable &&rhs) noexcept;

		DeltaPressable &operator=(const DeltaPressable &rhs) = delete;
		DeltaPressable &operator=(DeltaPressable &&rhs) noexcept;

		~DeltaPressable();

	private:
		void SetCallbacks();
		void RemoveCallbacks();
		void ClearCallbacks();
		void Update();

	private:
		Pressable* positive;
		Pressable* negative;
		Engine::Tools::Events::MemberFunction<DeltaPressable, void> updateFunction;
	};

}