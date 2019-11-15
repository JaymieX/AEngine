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
	explicit Mesh(Mesh&& mesh) noexcept;
	explicit Mesh(std::vector<Vertex>&);
	
   ~Mesh();

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};

class MeshRenderer final : public Component
{
public:
	MeshRenderer() = default;
	explicit MeshRenderer(Entity*, GLenum);
	explicit MeshRenderer(Entity*, GLenum, GLuint);
	explicit MeshRenderer(MeshRenderer&& renderer) noexcept;
	
   ~MeshRenderer() override;

	void Start() override;
	void Render() override;

	GLenum drawMode;

private:
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint modelLocId = 0;
	GLuint viewLocId = 0;
	GLuint projLocId = 0;
	GLuint textureLocId = 0;
	GLuint cameraPosLocId = 0;
	GLuint lightPosLocId = 0;
	GLuint ambientLocId = 0;
	GLuint diffuseLocId = 0;
	GLuint lightColorLocId = 0;
	GLuint textureId = 0;
	Mesh* meshPtr;
	Camera* cameraPtr;

	void GenBuffers();
};