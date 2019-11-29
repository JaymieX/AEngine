#pragma once
#include <Core/AEpch.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 uvCoords;
};

struct Mesh
{
	std::vector<Vertex> vertices = std::vector<Vertex>();
	std::vector<GLuint> indices = std::vector<GLuint>();
	GLuint textureId = 0;
};

struct MeshRenderData
{
	GLuint vao = 0;
	GLuint vbo = 0;
};