#include <Core/AEpch.h>
#include "Mesh.h"
#include "Shader.h"
#include "Components/Transform.h"
#include "Light.h"

Mesh::Mesh(std::vector<Vertex>& vertices) : vertices(vertices) {}

Mesh::Mesh(Mesh&& mesh) noexcept : vertices(mesh.vertices), indices(mesh.indices) { }

Mesh::~Mesh() { vertices.clear(); }

MeshRenderer::MeshRenderer(Entity* camera, const GLenum drawMode) : drawMode(drawMode),
																	meshPtr(nullptr),
																	cameraPtr(camera->GetComponent<Camera>())
																	{}

MeshRenderer::MeshRenderer(Entity* camera, const GLenum drawMode, const GLuint textureId): drawMode(drawMode),
                                                                                           meshPtr(nullptr),
                                                                                           cameraPtr(camera->GetComponent<Camera>())
{
	this->textureId = textureId;
}

MeshRenderer::MeshRenderer(MeshRenderer&& renderer) noexcept : drawMode(renderer.drawMode), meshPtr(nullptr), cameraPtr(renderer.cameraPtr) 
{
	vao = renderer.vao;
	vbo = renderer.vbo;
	modelLocId = renderer.modelLocId;
	viewLocId = renderer.viewLocId;
	projLocId = renderer.projLocId;
	textureLocId = renderer.textureLocId;
	cameraPosLocId = renderer.cameraPosLocId;
	lightPosLocId = renderer.lightPosLocId;
	ambientLocId = renderer.ambientLocId;
	diffuseLocId = renderer.diffuseLocId;
	lightColorLocId = renderer.lightColorLocId;
	textureId = renderer.textureId;
}


MeshRenderer::~MeshRenderer()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void MeshRenderer::Start()
{
	meshPtr = boundEntity->GetComponent<Mesh>();
	GenBuffers();
}

void MeshRenderer::Render()
{
	boundEntity->GetComponent<Shader>()->UseProgram();

	glUniform1i(textureLocId, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);

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
	glDrawArrays(drawMode, 0, static_cast<GLsizei>(meshPtr->vertices.size()));

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
	glBufferData(GL_ARRAY_BUFFER, meshPtr->vertices.size() * sizeof(Vertex), &meshPtr->vertices[0], GL_STATIC_DRAW);

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


