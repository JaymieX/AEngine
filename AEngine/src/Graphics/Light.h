#pragma once

#include "Systems/EntityComponent.h"

struct Light final : Component
{
	Light(const float ambient, const float diffuse, const glm::vec3 color) : ambient(ambient),
																			 diffuse(diffuse),
																			 color(color)
																			 {}
	float ambient, diffuse;
	glm::vec3 color;
};