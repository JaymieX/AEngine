#pragma once

#include "Physics/BoundingBox.h"

struct Plane {
	glm::vec4 plane;
	glm::vec3 normal;
	float distance;

	Plane() = default;
	explicit Plane(const glm::vec4 plane) : plane(plane), normal(glm::vec3(plane)), distance(plane.w) {}
};

class Frustum {
public:
	enum Planes
	{
		BOTTOM_P, TOP_P, NEAR_P, FAR_P, LEFT_P, RIGHT_P
	};

	void CreateFrustum(glm::mat4);
	bool Cull(BoundingBox*);

private: 

	Plane frustumPlanes[6];

	glm::vec3 GetPositiveVertex(const glm::vec3, BoundingBox*);
	glm::vec3 GetNegativeVertex(const glm::vec3, BoundingBox*);

};
