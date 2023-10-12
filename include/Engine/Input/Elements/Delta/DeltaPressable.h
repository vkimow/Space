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


	public:
		DeltaPressable(Pressable *const positive, Pressable *const negative, float threshold = 0.05f);
		DeltaPressable() = delete;

		~DeltaPressable();

	private:
		void SetCallbacks();
		void RemoveCallbacks();
		void Update();

	private:
		Pressable* const positive;
		Pressable* const negative;
		Engine::Tools::Events::MemberFunction<DeltaPressable, void> updateFunction;
	};

}