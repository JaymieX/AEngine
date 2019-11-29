#include <Core/AEpch.h>
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"
#include "Physics/BoundingBox.h"
#include "ObjLoader.h"
#include "Light.h"
#include "Camera.h"

Model::Model(ModelData& modelData) : modelData(modelData)
{
	objLoader = new ObjLoader();
	objLoader->LoadMeshData(modelData.objPath);
	meshes = objLoader->GetMeshData();
}

Model::~Model()
{
	if(objLoader) delete objLoader, objLoader = nullptr;
	
	for (auto renderData : renderMeshData)
	{
		glDeleteBuffers(1, &renderData.vbo);
		glDeleteVertexArrays(1, &renderData.vao);
	}
}

void Model::Start()
{
	GenBuffers();
	boundEntity->AddComponent<Transform>(modelData.position, modelData.scale, modelData.rotation);
	boundEntity->AddComponent<Shader>(modelData.shaderName, modelData.vertShaderPath, modelData.fragShaderPath);
	boundEntity->AddComponent<BoundingBox>();
}

void Model::Render()
{
	for(size_t i = 0; i < renderMeshData.size(); i++)
		Render(i);
}

void Model::Render(const size_t index)
{
	SetUniformData(index);
	
	const auto renderData = renderMeshData[index];
	glBindVertexArray(renderData.vao);
	glBindBuffer(GL_ARRAY_BUFFER, renderData.vbo);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(meshes[index].vertices.size()));

	glBindVertexArray(0);
	glUseProgram(0);
}

void Model::GenBuffers()
{
	for (auto currentMesh : meshes)
	{
		auto renderData = MeshRenderData{};
		glGenVertexArrays(1, &renderData.vao);
		glGenBuffers(1, &renderData.vbo);

		glBindVertexArray(renderData.vao);
		glBindBuffer(GL_ARRAY_BUFFER, renderData.vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * currentMesh.vertices.size(), &currentMesh.vertices[0], GL_STATIC_DRAW);

		BindVertexBuffers();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		renderMeshData.emplace_back(renderData);
	}
}


void Model::BindVertexBuffers()
{
	//Attribute Constants
	const auto positionId = 0;
	const auto normalId = 1;
	const auto colorId = 2;
	const auto uvCoordsId = 3;

	// Position Attribute
	glVertexAttribPointer(positionId, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(positionId);

	//Normal Attribute
	glVertexAttribPointer(normalId, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(normalId);

	//Color Attribute
	glVertexAttribPointer(colorId, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, color)));
	glEnableVertexAttribArray(colorId);

	//Texture Coordinate Attribute
	glVertexAttribPointer(uvCoordsId, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, uvCoords)));
	glEnableVertexAttribArray(uvCoordsId);
}


void Model::SetUniformData(const size_t index)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, meshes[index].textureId);
	
	//Get ShaderProgramID
	const auto shaderProgramId = boundEntity->GetComponent<Shader>()->GetShaderProgram();
	glUseProgram(shaderProgramId);

	const auto cameraComponent = modelData.cameraEntity->GetComponent<Camera>();
	const auto lightComponent = cameraComponent->GetLights()[0]->GetComponent<Light>();
	glUniform3fv(glGetUniformLocation(shaderProgramId, "cameraPos"), 1, glm::value_ptr(cameraComponent->GetPosition()));
	glUniform3fv(glGetUniformLocation(shaderProgramId, "light.position"), 1, glm::value_ptr(cameraComponent->GetLights()[0]->GetComponent<Transform>()->position));
	glUniform1f(glGetUniformLocation(shaderProgramId, "light.ambient"), lightComponent->ambient);
	glUniform1f(glGetUniformLocation(shaderProgramId, "light.diffuse"), lightComponent->diffuse);
	glUniform3fv(glGetUniformLocation(shaderProgramId, "light.color"), 1, glm::value_ptr(lightComponent->color));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, "view"), 1, GL_FALSE, glm::value_ptr(cameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, "projection"), 1, GL_FALSE, glm::value_ptr(cameraComponent->GetPerspectiveMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, "model"), 1, GL_FALSE, glm::value_ptr(boundEntity->GetComponent<Transform>()->GetTransformMatrix()));
}
