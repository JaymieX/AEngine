#include "Core/AEpch.h"
#include "Core/AEApplication.h"
#include "CollisionHandler.h"
#include "CollisionDetection.h"
#include "Ray.h"
#include "Rendering/GameObject.h"

Camera* CollisionHandling::cameraPtr = nullptr;
Ray CollisionHandling::ray;
std::unique_ptr<CollisionHandling> CollisionHandling::instance(nullptr);
std::vector<GameObject*> CollisionHandling::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandling::previousCollisions = std::vector<GameObject*>();

CollisionHandling* CollisionHandling::GetInstance()
{
	if (!instance) instance = std::unique_ptr<CollisionHandling>(new CollisionHandling());
	return instance.get();
}

void CollisionHandling::CreateHandler(Camera* cameraPointer)
{
	cameraPtr = cameraPointer;
	colliders.clear();
	previousCollisions.clear();
}

void CollisionHandling::AddGameObject(GameObject* gameObject)
{
	colliders.push_back(gameObject);
}

void CollisionHandling::Update(const glm::vec2 mousePos, int button)
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

void CollisionHandling::Render()
{
	ray.Render(cameraPtr);
}

void CollisionHandling::Destroy()
{
	for (auto collider : colliders)
		collider == nullptr;

	colliders.clear();
}
