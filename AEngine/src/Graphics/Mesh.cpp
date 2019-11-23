#include <Core/AEpch.h>
#include "Mesh.h"
#include "Shader.h"
#include "Components/Transform.h"
#include "Light.h"
#include "Graphics/ObjLoader.h"

Mesh::~Mesh() { if(objLoaderPtr) delete objLoaderPtr, objLoaderPtr = nullptr; }

Mesh::Mesh(std::string objPath)
{
	objLoaderPtr = new ObjLoader();
	objLoaderPtr->LoadMeshData(objPath);
	meshes = objLoaderPtr->GetMeshData();
}

Mesh::Mesh(const std::string objPath, const std::string materialPath)
{
	objLoaderPtr = new ObjLoader();
	objLoaderPtr->LoadMeshData(objPath, materialPath);
	meshes = objLoaderPtr->GetMeshData();
}

MeshFilter::MeshFilter(Mesh* meshPtr) : meshPtr(meshPtr) {}

MeshRenderer::MeshRenderer(Entity* camera, const GLenum drawMode) : drawMode(drawMode),
																	cameraPtr(camera->GetComponent<Camera>())
																	{}

MeshRenderer::~MeshRenderer()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void MeshRenderer::Start()
{
	meshPtr = boundEntity->GetComponent<MeshFilter>()->meshPtr;
	GenBuffers();
}

void MeshRenderer::Render()
{
	boundEntity->GetComponent<Shader>()->UseProgram();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUniform1i(textureLocId, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, meshPtr->meshes[0].textureId);

	glUniform3fv(cameraPosLocId, 1, glm::value_ptr(cameraPtr->GetPosition()));
	glUniform3fv(lightPosLocId, 1, glm::value_ptr(cameraPtr->GetLights()[0]->GetComponent<Transform>()->position));
	const auto lightComponent = cameraPtr->GetLights()[0]->GetComponent<Light>();
	
	glUniform1f(ambientLocId, lightComponent->ambient);
	glUniform1f(diffuseLocId, lightComponent->diffuse);
	glUniform3fv(lightColorLocId, 1, glm::value_ptr(lightComponent->color));
	
	glUniformMatrix4fv(viewLocId, 1, GL_FALSE, glm::value_ptr(cameraPtr->GetViewMatrix()));
	glUniformMatrix4fv(projLocId, 1, GL_FALSE, glm::value_ptr(cameraPtr->GetPerspectiveMatrix()));
	
	glBindVertexArray(vao);
	glUniformMatrix4fv(modelLocId, 1, GL_FALSE, glm::value_ptr(boundEntity->GetComponent<Transform>()->GetTransformMatrix()));
	//glDrawElements(drawMode, static_cast<GLsizei>(meshPtr->meshes[0].indices.size()), GL_UNSIGNED_INT, nullptr);
	glDrawArrays(drawMode, 0, meshPtr->meshes[0].vertices.size());

	glBindVertexArray(0);
}

void MeshRenderer::GenBuffers()
{
	//Attribute Constants
	const auto positionId = 0;
	const auto normalId = 1;
	const auto colorId = 2;
	const auto uvCoordsId = 3;

	//Create & Bind Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create & Bind Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, meshPtr->meshes[0].vertices.size() * sizeof(Vertex), &meshPtr->meshes[0].vertices[0], GL_STATIC_DRAW);

	//Create & Bind Index Buffer Object
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshPtr->meshes[0].indices.size() * sizeof(GLuint), &meshPtr->meshes[0].indices[0], GL_STATIC_DRAW);
	
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

	//Clear Binds
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Get ShaderProgramID
	const auto shaderProgramId = boundEntity->GetComponent<Shader>()->GetShaderProgram();
	
	modelLocId = glGetUniformLocation(shaderProgramId, "model");
	projLocId = glGetUniformLocation(shaderProgramId, "projection");
	viewLocId = glGetUniformLocation(shaderProgramId, "view");
	textureLocId = glGetUniformLocation(shaderProgramId, "inputTexture");
	cameraPosLocId = glGetUniformLocation(shaderProgramId, "cameraPos");
	lightPosLocId = glGetUniformLocation(shaderProgramId, "light.position");
	ambientLocId = glGetUniformLocation(shaderProgramId, "light.ambient");
	diffuseLocId = glGetUniformLocation(shaderProgramId, "light.diffuse");
	lightColorLocId = glGetUniformLocation(shaderProgramId, "light.color");
}


