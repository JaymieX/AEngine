#pragma once
#include <Core/AEpch.h>
#include "MaterialHandler.h"

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
	MaterialHandler::Material material;
};

struct MeshRenderData
{
	GLuint vao = 0;
	GLuint vbo = 0;
};