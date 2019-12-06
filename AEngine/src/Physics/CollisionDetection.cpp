#include <Core/AEpch.h>
#include "CollisionDetection.h"
#include "Ray.h"

Ray CollisionDetection::ViewportPointToRay(glm::vec2 mousePos, glm::vec2 screenSize, Camera* camera)
{
	glm::vec4 rayClip;
	rayClip.x = (2.0f * mousePos.x) / screenSize.x - 1.0f;
	rayClip.y = (2.0f * mousePos.y) / screenSize.y - 1.0f;
	rayClip.z = -1.0f;
	rayClip.w = 1.0f;
	//
	//rayClip.x = mousePos.x * 2.0f / screenSize.x - 1.0f;
	//rayClip.y = 1.0f - mousePos.y * 1.0f / screenSize.y;
	//rayClip.z = 0;
	//rayClip.w = 1;

	auto rayEye = glm::inverse(camera->GetPerspectiveMatrix()) * rayClip;
	rayEye.z = -1.0f;
	rayEye.w = 0.0f;
	
	const auto direction = glm::normalize(glm::vec3(glm::inverse(camera->GetViewMatrix()) * rayEye));

	const auto origin = camera->boundEntity->GetComponent<Transform>()->position;
	//const auto rayWorldSpace = glm::inverse(camera->GetViewMatrix()) * glm::inverse(camera->GetPerspectiveMatrix()) * rayClip;
	//const auto direction = glm::normalize(glm::vec3(rayWorldSpace) - origin);
	const auto rayDimensions = camera->GetClippingPlanes();
	
	return Ray(origin, direction, rayDimensions);
}

bool CollisionDetection::RayCastHit(Ray& ray, BoundingBox* boundingBox)
{
	auto model = boundingBox->boundEntity->GetComponent<Transform>()->GetTransformMatrix();
	const auto tMin = ray.dimensions.x;
	const auto tMax = ray.dimensions.y;

	const auto delta = glm::vec3(model[3]) - ray.origin;
	
	const auto xAxis = glm::vec3(model[0]);
	auto e = glm::dot(xAxis, delta);
	auto f = glm::dot(ray.direction, xAxis);
	if(!RayCastCheckAxis(e, f, boundingBox->transformedMinimum.x, boundingBox->transformedMaximum.x, tMin, tMax)) return false;

	const auto yAxis = glm::vec3(model[1]);
	e = glm::dot(yAxis, delta);
	f = glm::dot(ray.direction, yAxis);
	if(!RayCastCheckAxis(e, f, boundingBox->transformedMinimum.y, boundingBox->transformedMaximum.y, tMin, tMax)) return false;

	const auto zAxis = glm::vec3(model[2]);
	e = glm::dot(zAxis, delta);
	f = glm::dot(ray.direction, zAxis);
	if(!RayCastCheckAxis(e, f, boundingBox->transformedMinimum.z, boundingBox->transformedMaximum.z, tMin, tMax)) return false;

	ray.intersection = tMin;
	return true;
}

bool CollisionDetection::RayCastCheckAxis(const float e, const float f, const float min, const float max, float rayMin, float rayMax)
{
	if(abs(f) > 0.001)
	{
		auto t1 = (e + min) / f;
		auto t2 = (e + max) / f;
		if(t1 > t2) std::swap(t1, t2);
		rayMax = t2 < rayMax ? t2 : rayMax;
		rayMin = t1 > rayMin ? t1 : rayMin;
		if(rayMax < rayMin) return false;
	}
	if(-e + min > 0) return false;
	if(-e + max < 0) return false;
	return true;
}
