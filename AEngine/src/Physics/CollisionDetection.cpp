#include <Core/AEpch.h>
#include "CollisionDetection.h"
#include "Ray.h"

Ray CollisionDetection::ViewportPointToRay(glm::vec2 mousePos, glm::vec2 screenSize, Camera* camera)
{
	glm::vec4 startPoint;
	startPoint.x = (mousePos.x / screenSize.x - 0.5f) * 2.0f;
	startPoint.y = (mousePos.y / screenSize.y - 0.5f) * 2.0f;
	startPoint.z = -1.0f;
	startPoint.w = 1.0f;
	
	glm::vec4 endPoint;
	endPoint.x = (mousePos.x / screenSize.x - 0.5f) * 2.0f;
	endPoint.y = (mousePos.y / screenSize.y - 0.5f) * 2.0f;
	endPoint.z = 0.0f;
	endPoint.w = 1.0f;

	auto worldSpace = glm::inverse(camera->GetPerspectiveMatrix() * camera->GetViewMatrix());

	startPoint = startPoint * worldSpace;
	endPoint = endPoint * worldSpace;

	startPoint = startPoint / startPoint.w;
	endPoint = endPoint / endPoint.w;

	const auto direction = glm::normalize(startPoint - endPoint);
	
	return Ray(startPoint, direction, camera->GetClippingPlanes());
}

bool CollisionDetection::RayCastHit(Ray& ray, BoundingBox* boundingBox)
{
	auto model = boundingBox->boundEntity->GetComponent<Transform>()->GetTransformMatrix();
	auto tMin = ray.dimensions.x;
	auto tMax = ray.dimensions.y;

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

bool CollisionDetection::RayCastCheckAxis(const float e, const float f, const float min, const float max, float& rayMin, float& rayMax)
{
	if(fabs(f) > 0.001)
	{
		auto t1 = (e + min) / f;
		auto t2 = (e + max) / f;
		if(t1 > t2) std::swap(t1, t2);
		rayMax = t2 < rayMax ? t2 : rayMax;
		rayMin = t1 > rayMin ? t1 : rayMin;
		if(rayMax < rayMin) return false;
	}
	if(-e + min > 0.0f) return false;
	if(-e + max < 0.0f) return false;
	return true;
}
