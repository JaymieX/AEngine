#pragma once

#include <Systems/EntityComponent.h>
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Components/Transform.h"
#include "Rendering/GameObject.h"

constexpr void LimitScale(glm::vec3& v)
{
	v.x = v.x < 1.0f ? v.x / 2.0f : v.x;
	v.y = v.y < 1.0f ? v.y / 2.0f : v.y;
	v.z = v.z < 1.0f ? v.z / 2.0f : v.z;
}

struct BoundingBox final : Component
{
	explicit BoundingBox(const std::vector<Mesh>& meshes) : meshes(meshes){}
	
	void Start() override
	{
		transformPtr = boundEntity->GetComponent<Transform>(); 
		for(const auto& mesh : meshes)
		{
			for(auto vertex : mesh.vertices)
			{
				Minimum(vertex.position, minimum);
				Maximum(vertex.position, maximum);
			}
		}
		transformedMinimum = minimum;
		transformedMaximum = maximum;
	}

	void Update(const float dt) override
	{
		auto scaleFactor = transformPtr->scale;
		LimitScale(scaleFactor);
		transformedMaximum = maximum * scaleFactor;
		transformedMinimum = minimum * scaleFactor;
		//std::cout << "Model Scale: "<< glm::to_string(scaleFactor) << std::endl;
	}

	void Render() override
	{
		
	}

	void Print() const
	{
		std::cout << "Bounding Box Min: " << glm::to_string(minimum) << std::endl
				  << "Bounding Box Max: " << glm::to_string(maximum) << std::endl;
	}
	void PrintT() const
	{
		std::cout << "Bounding Box Min: " << glm::to_string(transformedMinimum) << std::endl
				  << "Bounding Box Max: " << glm::to_string(transformedMaximum) << std::endl;
	}
	
	glm::vec3 maximum = glm::vec3(0.0f);
	glm::vec3 minimum = glm::vec3(1.0f);
	glm::vec3 transformedMaximum = glm::vec3(0.0f);
	glm::vec3 transformedMinimum  = glm::vec3(1.0f);

	std::vector<Mesh> meshes;
	
	Transform* transformPtr = nullptr;
};


