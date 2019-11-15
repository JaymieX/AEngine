#include <Core/AEpch.h>
#include "GameObject.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"

GameObject::GameObject(Model* model, Shader* shader) : 
	model(model), shader(shader)
{
	
}

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
	mat3 normalMatrix = transformMatrix;
	glUniformMatrix4fv(transformMatrixID, 1, GL_FALSE, &transformMatrix[0][0]);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, &normalMatrix[0][0]);
}