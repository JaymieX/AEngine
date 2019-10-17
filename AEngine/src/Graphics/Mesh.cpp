#include <Core/AEpch.h>
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex*>& verticies) : verticies(verticies) {}

Mesh::~Mesh()
{
	verticies.clear();
}

MeshRenderer::MeshRenderer(Mesh* meshPtr, GLenum drawmode) : 
	meshPtr(meshPtr), drawmode(drawmode), vao(0), vbo(0) {}

MeshRenderer::~MeshRenderer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	delete meshPtr;
}

void MeshRenderer::GenBuffers()
{
	const int postionID = 0;
	const int normalID = 1;
	const int colorID = 2;
	const int uvCoordsID = 3;

	//Create & Bind Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create & Bind Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, meshPtr->verticies.size() * sizeof(Vertex), meshPtr->verticies.data(), GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(postionID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(postionID);

	//Normal Attribute
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(normalID);

	//Color Attribute
	glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(colorID);

	//Texture Coordinate Attribute
	glVertexAttribPointer(uvCoordsID, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(uvCoordsID);

}

void MeshRenderer::Render()
{
	glBindVertexArray(vao);
	glDrawArrays(drawmode, 0, static_cast<GLsizei>(meshPtr->verticies.size() * sizeof(Vertex)));
	glBindVertexArray(0);
}
