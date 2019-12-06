#include "Core/AEpch.h"
#include "Core/AEApplication.h"
#include "CollisionHandler.h"
#include "CollisionDetection.h"
#include "Ray.h"
#include "Rendering/GameObject.h"

Camera* CollisionHandler::cameraPtr = nullptr;
Ray CollisionHandler::ray;
std::unique_ptr<CollisionHandler> CollisionHandler::instance(nullptr);
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();

CollisionHandler* CollisionHandler::GetInstance()
{
	if (!instance) instance = std::unique_ptr<CollisionHandler>(new CollisionHandler());
	return instance.get();
}

void CollisionHandler::CreateHandler(Camera* cameraPointer)
{
	cameraPtr = cameraPointer;
	colliders.clear();
	previousCollisions.clear();
}

void CollisionHandler::AddGameObject(GameObject* gameObject)
{
	colliders.push_back(gameObject);
}

void CollisionHandler::Update(const glm::vec2 mousePos, int button)
{
	ray = CollisionDetection::ViewportPointToRay(mousePos, AEApplication::GetInstance()->GetWindowSize(), cameraPtr);
	GameObject* hitObject = nullptr;
	auto objectDistance = std::numeric_limits<float>::max();
	for (auto collider : colliders)
	{
		if (!ray.IsColliding(collider->GetCollider())) continue;
		if (ray.intersection >= objectDistance) continue;
		hitObject = collider;
		objectDistance = ray.intersection;
	}
	if(hitObject == nullptr) return;
	hitObject->SetHit(true, button);
	for(auto prev : previousCollisions)
	{
		if(prev != nullptr && prev != hitObject)
		{
			prev->SetHit(false, button);
			prev = nullptr;
		}
	}
	previousCollisions.clear();
	previousCollisions.push_back(hitObject);
}

void CollisionHandler::Render()
{
	ray.Render(cameraPtr);
}

void CollisionHandler::Destroy()
{
	for (auto collider : colliders)
		collider == nullptr;
	colliders.clear();
}
