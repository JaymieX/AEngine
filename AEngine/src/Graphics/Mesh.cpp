#include <Core/AEpch.h>
#include "Mesh.h"

Mesh::Mesh(GLenum drawmode, std::vector<Vertex*>& verticies) :
	drawmode(drawmode), verticies(verticies)
{
	GenBuffers();
}

Mesh::~Mesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	verticies.clear();
}

void Mesh::GenBuffers() 
{
	const int postionID		= 0;
	const int normalID		= 1;
	const int colorID		= 2;
	const int uvCoordsID	= 3;

	//Create & Bind Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	//Create & Bind Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies.data(), GL_STATIC_DRAW);
	
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

void Mesh::Render() const
{
	glBindVertexArray(vao);
	glDrawArrays(drawmode, 0, verticies.size());
	glBindVertexArray(0);
}
