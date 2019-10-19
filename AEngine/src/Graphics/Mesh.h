#pragma once

#include "Systems/EntityComponent.h"
#include "Graphics/Camera.h"

using namespace glm;

struct Vertex {
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 uvCoords;
};

struct Mesh final : public Component
{
public:
	Mesh() = default;
	Mesh(std::vector<Vertex>&);
	
   ~Mesh();

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};

class MeshRenderer final : public Component
{
public:
	MeshRenderer() = default;
	explicit MeshRenderer(Entity*, GLenum);
	
   ~MeshRenderer() override;

	void Start() override;
	void Render() override;

	GLenum drawMode;

private:
	GLuint vao, vbo;
	GLuint modelLocId, viewLocId, projLocId, textureLocId;
	Mesh* meshPtr;
	Camera* cameraPtr;

	void GenBuffers();
};