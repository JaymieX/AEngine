#pragma once

#include <Core/AEpch.h>
#include "Systems/EntityComponent.h"

struct Transform final : Component
{
	Transform() : angle(0), position(glm::vec3(0)),
				  rotationAxis(glm::vec3(0.0f, 1.0f, 0.0f)),
				  scale(glm::vec3(1.0f)) {}

	explicit Transform(const glm::vec3 position) : angle(0), position(position),
												   rotationAxis(glm::vec3(0.0f, 1.0f, 0.0f)),
												   scale(glm::vec3(1.0f)) {}

	[[nodiscard]] inline glm::mat4 GetTransformMatrix() const
	{
		glm::mat4 transformMatrix(1.0f);
		transformMatrix = glm::translate(transformMatrix, position);
		transformMatrix = glm::rotate(transformMatrix, glm::radians(angle), rotationAxis);
		transformMatrix = glm::scale(transformMatrix, scale);
		return transformMatrix;
	}
	
	float angle;
	glm::vec3 position;
	glm::vec3 rotationAxis;
	glm::vec3 scale;
};
