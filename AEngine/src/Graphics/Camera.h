#pragma once

#include "Systems/EntityComponent.h"
#include "Components/Transform.h"

class Camera final : public Component
{
public:
	Camera() = default;
	Camera(float, glm::vec2, bool lookAtEnabled = true);

	void Start() override;
	void Update(const float dt) override;
	void ResizeUpdate() override;

	void AddLight(Entity* light) { lights.emplace_back(light); }

	[[nodiscard]] inline std::vector<Entity*> GetLights() const { return lights; }
	[[nodiscard]] inline glm::vec2 GetClippingPlanes() const { return clipPlanes; }
	[[nodiscard]] inline glm::vec3 GetPosition() const { return transformPtr->position; }
	[[nodiscard]] inline glm::mat4 GetPerspectiveMatrix() const { return perspective; }
	[[nodiscard]] inline glm::mat4 GetOrthographicMatrix() const { return orthographic; }
	[[nodiscard]] inline glm::mat4 GetViewMatrix() const
	{
		//return glm::lookAt(transformPtr->position, glm::normalize(transformPtr->position - glm::vec3(0.0f)), up);
		return transformPtr->GetOrientationMatrix();
	}

private:
	void UpdateCameraOrientation();

	std::vector<Entity*> lights;


	Transform* transformPtr;
	bool lookAtEnabled = true;
	float fov = 0;
	glm::mat4 perspective, orthographic;
	glm::vec2 clipPlanes;
	glm::vec3 forward, up, right;
	glm::vec3 worldUp;
};
