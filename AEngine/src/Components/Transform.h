#pragma once

#include <Core/AEpch.h>
#include "Systems/EntityComponent.h"

struct TransformData
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(glm::vec4(0.0f));
};

class Transform final : public Component
{	
public:
	Transform() : position(glm::vec3(0)),
	              angleAxis(glm::vec3(0.0f, 1.0f, 0.0f)),
	              eulerAngles(glm::vec3(0)), scale(glm::vec3(1.0f)) {}

	explicit Transform(glm::vec3 position, 
					   glm::vec3 scale = glm::vec3(1.0f), 
					   glm::quat rotation = glm::quat(glm::vec4(0.0f))) :
					   rotation(rotation), position(position), angleAxis(glm::vec3(0.0f, 1.0f, 0.0f)),
					   eulerAngles(glm::vec3(0)), scale(scale) {}

	explicit Transform(const TransformData& data) : rotation(data.rotation), position(data.position), 
													angleAxis(glm::vec3(0.0f, 1.0f, 0.0f)), eulerAngles(glm::vec3(0.0f)),
													scale(data.scale) {}

	explicit Transform(TransformData&& data) : rotation(data.rotation), position(data.position), 
											   angleAxis(glm::vec3(0.0f, 1.0f, 0.0f)), eulerAngles(glm::vec3(0.0f)),
											   scale(data.scale) {}


	[[nodiscard]] glm::vec3 GetEuler() const { return eulerAngles; }
	
	[[nodiscard]] glm::mat4 GetTransformMatrix() const
	{
		auto transformMatrix = glm::mat4(1.0f);
		transformMatrix = GetTranslationMatrix(transformMatrix);
		transformMatrix = GetRotationMatrix(transformMatrix);
		transformMatrix = GetScalingMatrix(transformMatrix);
		return transformMatrix;
	}

	[[nodiscard]] glm::mat4 GetOrientationMatrix() const
	{
		auto matrix = glm::mat4(1.0f);
		matrix = GetRotationMatrix(matrix);
		matrix = GetTranslationMatrix(matrix);
		return matrix;
	}

	void Start() override { ConvertRotation(); }
	void Update(const float dt) override { ConvertRotation(); }  
	
	float angle = 0;
	glm::quat rotation = glm::quat(glm::vec4(0.0f));
	glm::vec3 position;
	glm::vec3 angleAxis;
	glm::vec3 eulerAngles;
	glm::vec3 scale;
private:
	[[nodiscard]] glm::mat4 GetTranslationMatrix(const glm::mat4 mat) const
	{
		return glm::translate(mat, position);
	}

	[[nodiscard]] glm::mat4 GetRotationMatrix(const glm::mat4 mat) const
	{
		return mat * glm::mat4_cast(rotation);
	}

	[[nodiscard]] glm::mat4 GetScalingMatrix(const glm::mat4 mat) const
	{
		return glm::scale(mat, scale);
	}

	void ConvertRotation() { eulerAngles = glm::eulerAngles(rotation); }
};
