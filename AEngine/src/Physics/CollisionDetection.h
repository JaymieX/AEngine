#pragma once
#include "Graphics/Camera.h"

struct BoundingBox;
struct Ray;

class CollisionDetection
{
public:
	CollisionDetection() = delete;
	~CollisionDetection() = delete;

	static Ray ViewportPointToRay(glm::vec2, glm::vec2, Camera*);
	static bool RayCastHit(Ray&, BoundingBox*);

private:
	static bool RayCastCheckAxis(float, float, float, float, float&, float&);
};

