#pragma once

#include <Core/AEpch.h>
#include "Systems/EntityComponent.h"

struct Transform final : Component
{
	Transform() : angle(0), position(glm::vec3(0)),
				  angleAxis(glm::vec3(0.0f, 1.0f, 0.0f)),
				  scale(glm::vec3(1.0f)) {}

	explicit Transform(const glm::vec3 position) : angle(0), position(position),
												   angleAxis(glm::vec3(0.0f, 1.0f, 0.0f)),
												   scale(glm::vec3(1.0f)) {}

	[[nodiscard]] inline glm::mat4 GetTransformMatrix() const
	{
		glm::mat4 transformMatrix(1.0f);
		transformMatrix = glm::translate(transformMatrix, position);
		transformMatrix = glm::rotate(transformMatrix, glm::radians(angle), angleAxis);
		transformMatrix = glm::scale(transformMatrix, scale);
		return transformMatrix;
	}

	void Start() override
	{
		ConvertRotation();
	}

	void Update() override
	{
		ConvertRotation();
	}
	
	float angle = 0;
	glm::quat rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 eulerAngles;
	glm::vec3 position;
	glm::vec3 angleAxis;
	glm::vec3 scale;

private:
	void ConvertRotation()
	{
		eulerAngles = glm::eulerAngles(rotation);
		//angle = glm::angle(rotation);
		//angleAxis = glm::axis(rotation);
	}
};
