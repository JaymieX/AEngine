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

struct MeshData
{
	std::vector<Vertex> vertices = std::vector<Vertex>();
	std::vector<GLuint> indices = std::vector<GLuint>();
	GLuint textureId = 0;
};

//struct Mesh final : public Component
//{
//public:
//	Mesh() = default;
//   ~Mesh();
//	
//	explicit Mesh(Mesh&& mesh) noexcept;
//	explicit Mesh(std::vector<Vertex>&);
//	explicit Mesh(MeshData*, GLuint);
//
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//	
//	MeshData* subMeshPtr;
//	GLuint shaderProgramId = 0;
//};

class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	explicit Mesh(std::string);
	explicit Mesh(std::string, std::string);

	std::vector<MeshData> meshes;
private:
	class ObjLoader* objLoaderPtr;
};

struct MeshFilter final : public Component
{
	MeshFilter() = default;
	explicit MeshFilter(Mesh*);
	Mesh* meshPtr = nullptr;
};

class MeshRenderer final : public Component
{
public:
	MeshRenderer() = default;
	explicit MeshRenderer(Entity*, GLenum);
	
   ~MeshRenderer() override;

	void Start() override;
	void Render() override;

	GLenum drawMode = GL_TRIANGLES;

private:
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ebo = 0;
	GLuint modelLocId = 0;
	GLuint viewLocId = 0;
	GLuint projLocId = 0;
	GLuint textureLocId = 0;
	GLuint cameraPosLocId = 0;
	GLuint lightPosLocId = 0;
	GLuint lightColorLocId = 0;
	GLuint ambientLocId = 0;
	GLuint diffuseLocId = 0;
	
	Mesh* meshPtr = nullptr;
	Camera* cameraPtr = nullptr;

	void GenBuffers();
};