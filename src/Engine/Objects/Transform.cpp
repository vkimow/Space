#include "Engine/Objects/Transform.h"
#include <iostream>

namespace Engine::Objects
{
	Transform::Transform()
		: position()
		, orientation()
		, scale(1.0f)
	{};

	Transform::Transform(glm::vec3 position)
		: Transform(position, glm::quat())
	{};

	Transform::Transform(glm::vec3 position, glm::quat orientation)
		: Transform(position, orientation, glm::vec3(1.0f))
	{};

	Transform::Transform(glm::vec3 position, glm::vec3 scale)
		: Transform(position, glm::quat(), scale)
	{};

	Transform::Transform(glm::vec3 position, glm::quat orientation, glm::vec3 scale)
		: position(position)
		, orientation(orientation)
		, scale(scale)
	{};

	Transform::Transform(const Transform &rhs)
		: position(rhs.position)
		, orientation(rhs.orientation)
		, scale(rhs.scale)
	{};

	Transform::Transform(Transform &&rhs) noexcept
		: position(std::move(rhs.position))
		, orientation(std::move(rhs.orientation))
		, scale(std::move(rhs.scale))
	{};

	Transform &Transform::operator=(const Transform &rhs)
	{
		position = rhs.position;
		orientation = rhs.orientation;
		scale = rhs.scale;
		return *this;
	}

	Transform &Transform::operator=(Transform &&rhs) noexcept
	{
		position = std::move(rhs.position);
		orientation = std::move(rhs.orientation);
		scale = std::move(rhs.scale);
		return *this;
	}

	Transform::~Transform() {}

	glm::mat4 Transform::GetTransformMatrix()
	{
		glm::mat4 matrix(1.0f);
		matrix = glm::translate(matrix, position);
		matrix *= glm::mat4_cast(orientation);
		matrix = glm::scale(matrix, scale);
		return std::move(matrix);
	}

	Transform::operator std::string() const
	{
		std::ostringstream oss;
		glm::vec3 orientationInDegrees = glm::degrees(GetEurlerOrientation());
		oss << "P:(" << position.x << ',' << position.y << position.z << ") "
			<< "R:(" << orientationInDegrees.x << ',' << orientationInDegrees.y << orientationInDegrees.z << ") "
			<< "P:(" << scale.x << ',' << scale.y << scale.z << ")";
		return oss.str();
	}
}