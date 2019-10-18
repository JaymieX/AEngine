#include <Core/AEpch.h>
#include "Mesh.h"
#include "Shader.h"
#include "Components/Transform.h"

Mesh::Mesh(std::vector<Vertex>& vertices) : vertices(vertices) {}

Mesh::~Mesh()
{
	vertices.clear();
}

MeshRenderer::MeshRenderer(Entity* camera, const GLenum drawMode) : drawMode(drawMode), vao(0), vbo(0), modelLocId(0), viewLocId(0),
																	projLocId(0), textureLocId(0), camera(camera->GetComponent<Camera>())
																	{}

MeshRenderer::~MeshRenderer()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void MeshRenderer::Start()
{
	mesh = boundEntity->GetComponent<Mesh>();
	GenBuffers();
}

void MeshRenderer::Render()
{
	boundEntity->GetComponent<Shader>().UseProgram();

	glUniformMatrix4fv(viewLocId, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
	glUniformMatrix4fv(projLocId, 1, GL_FALSE, glm::value_ptr(camera.GetPerspectiveMatrix()));
	
	glBindVertexArray(vao);
	glUniformMatrix4fv(modelLocId, 1, GL_FALSE, glm::value_ptr(boundEntity->GetComponent<Transform>().GetTransformMatrix()));
	glDrawArrays(drawMode, 0, static_cast<GLsizei>(mesh.vertices.size()));

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
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

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
	const auto shaderProgramId = boundEntity->GetComponent<Shader>().GetShaderProgram();
	
	modelLocId = glGetUniformLocation(shaderProgramId, "model");
	projLocId = glGetUniformLocation(shaderProgramId, "projection");
	viewLocId = glGetUniformLocation(shaderProgramId, "view");
}


