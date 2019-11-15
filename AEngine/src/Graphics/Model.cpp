#include <Core/AEpch.h>
#include "Model.h"
#include "Mesh.h"
#include "Systems/EntityComponent.h"
#include "Components/Transform.h"

Model::Model(EntityManager* manager, std::string objPath, std::string materialPath, GLuint shaderProgramId)
{
	modelEntityPtr = manager->CreateAndAddEntity();
	
	transformComponentPtr = modelEntityPtr->AddComponent<Transform>();
	meshComponentPtr = modelEntityPtr->AddComponent<Mesh>();
	meshRendererComponent = modelEntityPtr->AddComponent<MeshRenderer>();
}

void Model::CreateSubModel(glm::vec3 pos, float angle, glm::vec3 rotationAxis, glm::vec3 scale)
{
	auto subModel = new Model();
}

void Model::UpdateSubModel(int index, glm::vec3 pos, float angle, glm::vec3 rotationAxis, glm::vec3 scale)
{
	auto smTransformComponent = modelEntityPtr->GetChild(index)->GetComponent<Transform>();
	smTransformComponent->position = pos;
	smTransformComponent->angle = angle;
	smTransformComponent->rotationAxis = rotationAxis,
	smTransformComponent->scale = scale;
}

glm::mat4 Model::GetModelMatrix(int index)
{
	return modelEntityPtr->GetChild(index)->GetComponent<Transform>()->GetTransformMatrix();
}


