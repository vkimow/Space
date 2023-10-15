#pragma once

#include "Engine/Input/Main/Element.h"
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
		virtual ~Vector();

	public:
        float IsZero() const { return isZero; }
		float IsNotZero() const { return !isZero; }
		glm::vec2 GetVector() const { return vector; }

	protected:
		void ChangeVector(float x, float y);
		void ChangeVector(glm::vec2 value);
		void ChangeX(float value);
		void ChangeY(float value);

	private:
		CREATE_ACTION(glm::vec2, OnVectorChange);

	private:
        bool isZero;
		glm::vec2 vector;
		float threshold;
	};

}

