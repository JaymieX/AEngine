#pragma once

#include <Systems/EntityComponent.h>
#include "Graphics/Mesh.h"

constexpr float Magnitude(glm::vec3 v){ return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);} 

struct BoundingBox : Component
{
	BoundingBox() = default;
	BoundingBox(glm::mat4 transform) : transformationMatrix(transform) {}

	void Start() override
	{
		auto meshes = boundEntity->GetComponent<MeshFilter>()->meshPtr->meshes;
		for(const auto& mesh : meshes)
		{
			for(auto vertex : mesh.vertices)
			{
				if(Magnitude(vertex.position) > Magnitude(maximum))
					maximum = vertex.position;

				if(Magnitude(vertex.position) < Magnitude(minimum))
					minimum = vertex.position;
			}
		}
	}

	void SetMinMax(glm::vec3 min, glm::vec3 max) { minimum = min; maximum = max; }
	
	glm::vec3 maximum = glm::vec3(0.0f);
	glm::vec3 minimum = glm::vec3(0.0f);
	glm::mat4 transformationMatrix = glm::mat4(0.0f);
};


