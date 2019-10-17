#pragma once

#include "Systems/EntityComponent.h"

using namespace glm;

struct Vertex {
	vec3 position;
	vec3 normals;
	vec3 color;
	vec2 uvCoords;
};

struct Mesh
{
public:
	Mesh(std::vector<Vertex*>&);
   ~Mesh();

	std::vector<Vertex*> verticies;
	std::vector<GLuint> indices;
};

class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh*, GLenum);
	~MeshRenderer() override;

	void Start() override { GenBuffers(); }
	void Render() override;

	GLenum drawmode;

private:
	GLuint vao, vbo;
	Mesh* meshPtr;

	void GenBuffers();
};