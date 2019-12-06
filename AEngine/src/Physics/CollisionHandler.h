#pragma once

class GameObject;
class Camera;

class CollisionHandler
{
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();

	void CreateHandler(Camera*);
	void AddGameObject(GameObject*);
	void Update(glm::vec2, int);
	void Render();
	void Destroy();

private:
	CollisionHandler() = default;
	~CollisionHandler() = default;

	static std::vector<GameObject*> colliders;
	static std::vector<GameObject*> previousCollisions;
	static Camera* cameraPtr;
	static class Ray ray;

	static std::unique_ptr<CollisionHandler> instance;
	friend std::default_delete<CollisionHandler>;
};
