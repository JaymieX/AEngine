#include "Core/AEpch.h"
#include "Frustum.h"

void Frustum::CreateFrustum(glm::mat4 frustumMatrix)
{
	frustumPlanes[BOTTOM_P] = Plane(glm::vec4(
		frustumMatrix[0][3] + frustumMatrix[0][1],
		frustumMatrix[1][3] + frustumMatrix[1][1],
		frustumMatrix[2][3] + frustumMatrix[2][1],
		frustumMatrix[3][3] + frustumMatrix[3][1]
	));

	frustumPlanes[TOP_P] = Plane(glm::vec4(
		frustumMatrix[0][3] - frustumMatrix[0][1],
		frustumMatrix[1][3] - frustumMatrix[1][1],
		frustumMatrix[2][3] - frustumMatrix[2][1],
		frustumMatrix[3][3] - frustumMatrix[3][1]
	));

	frustumPlanes[NEAR_P] = Plane(glm::vec4(
		frustumMatrix[0][3] - frustumMatrix[0][2],
		frustumMatrix[1][3] - frustumMatrix[1][2],
		frustumMatrix[2][3] - frustumMatrix[2][2],
		frustumMatrix[3][3] - frustumMatrix[3][2]
	));

	frustumPlanes[FAR_P] = Plane(glm::vec4(
		frustumMatrix[0][2],
		frustumMatrix[1][2],
		frustumMatrix[2][2],
		frustumMatrix[3][2]
	));

	frustumPlanes[LEFT_P] = Plane(glm::vec4(
		frustumMatrix[0][3] - frustumMatrix[0][0],
		frustumMatrix[1][3] - frustumMatrix[1][0],
		frustumMatrix[2][3] - frustumMatrix[2][0],
		frustumMatrix[3][3] - frustumMatrix[3][0]
	));

	frustumPlanes[RIGHT_P] = Plane(glm::vec4(
		frustumMatrix[0][3] + frustumMatrix[0][0],
		frustumMatrix[1][3] + frustumMatrix[1][0],
		frustumMatrix[2][3] + frustumMatrix[2][0],
		frustumMatrix[3][3] + frustumMatrix[3][0]
	));

	for (auto& frustumPlane : frustumPlanes)
	{
		frustumPlane.distance /= glm::length(frustumPlane.normal);
		frustumPlane.normal = glm::normalize(frustumPlane.normal);
		//frustumPlane = glm::normalize(frustumPlane.plane);
	}
}

bool Frustum::Cull(BoundingBox* boundingBox)
{
	for (auto& frustumPlane : frustumPlanes)
	{
		if (frustumPlane.distance + glm::dot(frustumPlane.normal, GetPositiveVertex(frustumPlane.normal, boundingBox)) < 0.0f) {
			return false;
		}
		if (frustumPlane.distance + glm::dot(frustumPlane.normal, GetNegativeVertex(frustumPlane.normal, boundingBox)) < 0.0f) {
			return true;
		}
	}

	return true;
}

glm::vec3 Frustum::GetPositiveVertex(const glm::vec3 normal, BoundingBox* boundingBox)
{
	auto positiveVertex = boundingBox->transformedMinimum;

	if (normal.x >= 0.f) positiveVertex.x = boundingBox->transformedMaximum.x;
	if (normal.y >= 0.f) positiveVertex.y = boundingBox->transformedMaximum.y;
	if (normal.z >= 0.f) positiveVertex.z = boundingBox->transformedMaximum.z;

	return positiveVertex;
}

glm::vec3 Frustum::GetNegativeVertex(const glm::vec3 normal, BoundingBox* boundingBox)
{
	auto negativeVertex = boundingBox->transformedMaximum;

	if (normal.x >= 0.f) negativeVertex.x = boundingBox->transformedMinimum.x;
	if (normal.y >= 0.f) negativeVertex.y = boundingBox->transformedMinimum.y;
	if (normal.z >= 0.f) negativeVertex.z = boundingBox->transformedMinimum.z;

	return negativeVertex;
}

