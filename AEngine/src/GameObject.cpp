#include <AEpch.h>
#include "GameObject.h"
#include "Model.h"

GameObject::GameObject(Model* model, Shader* shader) : 
	model(model), shader(shader) { }

GameObject::~GameObject()
{
	if (model) delete model, model = nullptr;
	if (shader) delete shader, shader = nullptr;
}

void GameObject::Update(float dt)
{

}

void GameObject::Render() const
{

	if(model) model->Render();
}