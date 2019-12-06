#pragma once

class Model;
class Entity;
class GameObject;

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph) = delete;

	static SceneGraph* GetInstance();

	void AddModel(Model*);
	void AddGameObject(class GameObject*, std::string);

	class GameObject* GetGameObjects(std::string);

	void Update(float dt);
	void Render();

	static std::map<std::string, std::unique_ptr<GameObject>>& GetGameObjects() { return gameObjects; }
private:
	SceneGraph() = default;
	~SceneGraph();

	static std::map<GLuint, std::vector<Model*>> shaderModels;
	static std::map<std::string, std::unique_ptr<GameObject>> gameObjects;

	static std::unique_ptr<SceneGraph> instance;
	friend std::default_delete<SceneGraph>;
};