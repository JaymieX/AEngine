#pragma once
#include "Core/Logger.h"

class CollisionHandler;
class Model;
class EntityManager;
struct BoundingBox;

class GameObject
{
public:
	GameObject() = default;
	GameObject(EntityManager*, Model*);
	GameObject(EntityManager*, struct TransformData&, Model*);
	~GameObject();

	void Update(float) const;
	void Render() const;

	void SetName(const std::string& name) { this->name = name; }
	[[nodiscard]] std::string GetName() const { return name; }
	[[nodiscard]] BoundingBox* GetCollider() const { return boundingBoxPtr; }
	[[nodiscard]] bool GetHit() const { return isHit; }
private:
	std::string name = std::string();
	std::unique_ptr<Model> modelPtr;

	friend CollisionHandler;
	void SetHit(const bool hit, const int mouseBtn)
	{
		isHit = hit;
		LOG_INFO(GetName() + std::string("On Ray Collider Hit : Button Pressed ") + std::to_string(mouseBtn), "Gameobject.h", __LINE__);
	}

	bool isHit = false;

	class Entity* entity = nullptr;
	class Transform* transformPtr = nullptr;
	BoundingBox* boundingBoxPtr = nullptr;
};