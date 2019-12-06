#include <Core/AEpch.h>
#include "Core/AEApplication.h"
#include "Camera.h"
#include "Light.h"

Camera::Camera(const float fov, const glm::vec2 clipPlanes, bool lookAtEnabled) : transformPtr(nullptr),
                                                                                  lookAtEnabled(lookAtEnabled),
                                                                                  fov(fov),
                                                                                  perspective(glm::mat4(1.0f)),
                                                                                  orthographic(perspective),
                                                                                  clipPlanes(clipPlanes),
                                                                                  forward(glm::vec3(0.0f, 0.0f, -1.0f)),
                                                                                  up(glm::vec3(0.0f, 1.0f, 0.0f)),
                                                                                  right(0.0f), worldUp(up)
{
}

void Camera::Start()
{
	transformPtr = boundEntity->GetComponent<Transform>();

	perspective = glm::perspective(fov, AEApplication::GetInstance()->GetWindowSize().x / AEApplication::GetInstance()->GetWindowSize().y, 
			 clipPlanes.x, clipPlanes.y);

	orthographic = glm::ortho(0.0f, AEApplication::GetInstance()->GetWindowSize().x, 0.0f, 
				AEApplication::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraOrientation();
}

void Camera::Update(const float dt)
{
	UpdateCameraOrientation();
}

void Camera::ResizeUpdate()
{
	perspective = glm::perspective(fov, AEApplication::GetInstance()->GetWindowSize().x / AEApplication::GetInstance()->GetWindowSize().y,
		clipPlanes.x, clipPlanes.y);

	orthographic = glm::ortho(0.0f, AEApplication::GetInstance()->GetWindowSize().x, 0.0f,
		AEApplication::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraOrientation();
}

void Camera::UpdateCameraOrientation()
{
	forward.x = cos(glm::radians(transformPtr->angleAxis.x)) * cos(glm::radians(transformPtr->angleAxis.y));
	forward.y = sin(glm::radians(transformPtr->angleAxis.y));
	forward.z = sin(glm::radians(transformPtr->angleAxis.x)) * cos(glm::radians(transformPtr->angleAxis.y));
	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));

	//frustum.CreateFrustum(GetPerspectiveMatrix() * GetViewMatrix());
}
