#pragma once

#include "Graphics/Mesh.h"
#include "Physics/BoundingBox.h"

class ObjLoader
{
public:
	~ObjLoader();

	void LoadMeshData(const std::string& fileName);
	void LoadMeshData(const std::string& fileName, const std::string& matName);
	
	[[nodiscard]] std::vector<Vertex> GetVertices() const { return meshVertices; }
	[[nodiscard]] std::vector<GLuint> GetIndices() const { return indices; }
	[[nodiscard]] std::vector<Mesh> GetMeshData() const { return meshes; }

private:
	std::vector<glm::vec3> vertices = std::vector<glm::vec3>();
	std::vector<glm::vec3> normals = std::vector<glm::vec3>();
	std::vector<glm::vec2> uvCoords = std::vector<glm::vec2>();
	std::vector<GLuint> indices = std::vector<GLuint>();
	std::vector<GLuint> normalIndices = std::vector<GLuint>();
	std::vector<GLuint> uvIndices = std::vector<GLuint>();
	std::vector<Vertex> meshVertices = std::vector<Vertex>();
	std::vector<Mesh> meshes = std::vector<Mesh>();

	GLuint currentTexture = 0;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName);
	void LoadMaterialLibrary(const std::string& matName);
};
