#include <Core/AEpch.h>
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex*>& verticies) : verticies(verticies) {}

Mesh::~Mesh()
{
	verticies.clear();
}

MeshRenderer::MeshRenderer(GLenum drawMode) : drawMode(drawMode),
                                              vao(0), vbo(0) {}

MeshRenderer::~MeshRenderer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void MeshRenderer::Start()
{
	mesh = owner->getComponent<Mesh>();
	GenBuffers();
}

void MeshRenderer::Render()
{
	glBindVertexArray(vao);
	const auto size = static_cast<GLsizei>(mesh.verticies.size() * sizeof(Vertex));
	glDrawArrays(drawMode, 0, size);
	glBindVertexArray(0);
}

void MeshRenderer::GenBuffers()
{
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
	glBufferData(GL_ARRAY_BUFFER, mesh.verticies.size() * sizeof(Vertex), mesh.verticies.data(), GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(positionId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(positionId);

	//Normal Attribute
	glVertexAttribPointer(normalId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(normalId);

	//Color Attribute
	glVertexAttribPointer(colorId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<GLvoid*>(offsetof(Vertex, color)));
	glEnableVertexAttribArray(colorId);

	//Texture Coordinate Attribute
	glVertexAttribPointer(uvCoordsId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<GLvoid*>(offsetof(Vertex, uvCoords)));
	glEnableVertexAttribArray(uvCoordsId);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


