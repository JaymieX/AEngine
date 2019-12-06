#include <Core/AEpch.h>
#include "SceneGraph.h"
#include "Graphics/Model.h"
#include "GameObject.h"
#include "Physics/CollisionHandler.h"

std::unique_ptr<SceneGraph> SceneGraph::instance(nullptr);
std::map<GLuint, std::vector<Model*>> SceneGraph::shaderModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, std::unique_ptr<GameObject>> SceneGraph::gameObjects = std::map<std::string, std::unique_ptr<GameObject>>();

SceneGraph* SceneGraph::GetInstance()
{
	if(!instance) instance = std::unique_ptr<SceneGraph>(new SceneGraph());
	return instance.get();
}

SceneGraph::~SceneGraph()
{
	//gameObjects.clear();
}

void SceneGraph::AddModel(Model* modelComponent)
{
	const auto shaderProgram = modelComponent->GetShaderProgram();
	auto it = shaderModels.find(shaderProgram);
	if(it != shaderModels.end())
		it->second.push_back(modelComponent);
	shaderModels.emplace(std::make_pair(shaderProgram, std::vector<Model*>()));
	shaderModels[shaderProgram].push_back(modelComponent);
}

void SceneGraph::AddGameObject(GameObject* gameObjectPtr, std::string name)
{
	if(gameObjects.find(name) != gameObjects.end()) return;
	if(name.empty()) name = "GameObject_" + gameObjects.size();
	gameObjects.emplace(std::make_pair(name, std::unique_ptr<GameObject>(gameObjectPtr)));
	CollisionHandling::GetInstance()->AddGameObject(gameObjectPtr);
}

GameObject* SceneGraph::GetGameObjects(const std::string name)
{
	const auto it = gameObjects.find(name);
	if(it != gameObjects.end())
		return it->second.get();
	return nullptr;
}

void SceneGraph::Update(const float dt)
{
	for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		it->second->Update(dt);
}

void SceneGraph::Render()
{
	CollisionHandling::GetInstance()->Render();
	for(const auto shaderModel : shaderModels) 
	{
		glUseProgram(shaderModel.first);
		for(auto model : shaderModel.second)
			model->Render();
	}
}