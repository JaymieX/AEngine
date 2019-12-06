#include <Core/AEpch.h>
#include "GameObject.h"
#include "Systems/EntityComponent.h"
#include "Components/Transform.h"
#include "Graphics/Model.h"
#include "Physics/BoundingBox.h"

GameObject::GameObject(EntityManager* manager, Model* modelPtr) : modelPtr(std::unique_ptr<Model>(modelPtr))
{
	entity			= manager->CreateAndAddEntity();
	transformPtr	= entity->AddComponent<Transform>();
	boundingBoxPtr	= entity->AddComponent<BoundingBox>(modelPtr->GetMeshes());
}

GameObject::GameObject(EntityManager* manager, TransformData& transformData, Model* modelPtr) : modelPtr(std::unique_ptr<Model>(modelPtr))
{
	entity			= manager->CreateAndAddEntity();
	transformPtr	= entity->AddComponent<Transform>(transformData);
	boundingBoxPtr	= entity->AddComponent<BoundingBox>(modelPtr->GetMeshes());
}

GameObject::~GameObject() { entity->Destroy(); }

void GameObject::Update(const float dt) const
{
	transformPtr->Update(dt);
	boundingBoxPtr->Update(dt);
	modelPtr->SetModelMatrix(transformPtr->GetTransformMatrix());
}

void GameObject::Render() const
{
	modelPtr->Render();
}

