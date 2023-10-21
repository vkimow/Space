#pragma once

#include "Engine/Input/Main/Element.h"
#include "Engine/Input/Elements/Delta/Delta.h"
#include "Engine/Tools/Events/Action.h"
#include "glm/glm.hpp"

namespace Engine::Input
{
	class  Vector : public Element
	{
		friend class InputModule;
		friend class Scheme;
		friend class Mouse;

	protected:
		Vector();
		Vector(float threshold);

	public:
		Vector(const Vector &rhs) = delete;
		Vector(Vector &&rhs) noexcept;

		Vector &operator=(const Vector &rhs) = delete;
		Vector &operator=(Vector &&rhs) noexcept;

		virtual ~Vector();

	public:
        float IsZero() const { return isZero; }
		float IsNotZero() const { return !isZero; }
		glm::vec2 GetVector() const { return vector; }

	public:
		float GetThreshold() { return threshold; }
		void SetThreshold(float value) { threshold = value; }

	protected:
		void ChangeVector(float x, float y);
		void ChangeVector(glm::vec2 value);
		void ChangeX(float value);
		void ChangeY(float value);

	public:
		CREATE_ACTION(glm::vec2, OnVectorChange);

	public:
		Delta *const GetDeltaX();
		Delta *const GetDeltaY();

	private:
        bool isZero;
		glm::vec2 vector;
		float threshold;

	private:
		Delta *deltaX;
		Delta *deltaY;
	};

}

