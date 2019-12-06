#pragma once

class GameObject;
class Camera;

class CollisionHandling
{
public:
	CollisionHandling(const CollisionHandling&) = delete;
	CollisionHandling(CollisionHandling&&) = delete;
	CollisionHandling& operator=(const CollisionHandling&) = delete;
	CollisionHandling& operator=(CollisionHandling&&) = delete;

	static CollisionHandling* GetInstance();

	void CreateHandler(Camera*);
	void AddGameObject(GameObject*);
	void Update(glm::vec2, int);
	void Render();
	void Destroy();

private:
	CollisionHandling() = default;
	~CollisionHandling() = default;

	static std::vector<GameObject*> colliders;
	static std::vector<GameObject*> previousCollisions;
	static Camera* cameraPtr;
	static class Ray ray;

	static std::unique_ptr<CollisionHandling> instance;
	friend std::default_delete<CollisionHandling>;
};
