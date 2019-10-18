#pragma once

#include "Systems/EntityComponent.h"
#include "Components/Transform.h"

class Camera : public Component
{
public:
	Camera() = default;
	Camera(const float, const glm::vec2);
	
	void Start() override;
	void Update() override;
	
	[[nodiscard]] inline glm::mat4 GetViewMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), transform.position);
	}

	[[nodiscard]] inline glm::mat4 GetPerspectiveMatrix() const { return perspective; }
	[[nodiscard]] inline glm::mat4 GetOrthographicMatrix() const { return orthographic; }


private:
	void UpdateCameraOrientation();

	Transform transform;
	
	float fov = 0;
	glm::mat4 perspective, orthographic;
	glm::vec2 clipPlanes;
	glm::vec3 forward, up, right;
	glm::vec3 worldUp;
	
};
