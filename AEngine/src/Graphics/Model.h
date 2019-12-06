#pragma once

#include "Mesh.h"
class Camera;

struct ModelData
{
	class Entity* camera = nullptr;
	GLuint shaderProgram = 0;
	std::string objPath = std::string();
	std::string materialPath = std::string();
};

class Model
{
public:
	explicit Model(const ModelData&);
	explicit Model(ModelData&&);
	~Model();

	void Render();
	void Render(size_t index);

	[[nodiscard]] std::vector<Mesh> GetMeshes() const { return meshes; }
	[[nodiscard]] GLuint GetShaderProgram() const  { return modelData.shaderProgram; }
	void SetModelMatrix(const glm::mat4 modelMatrix){ this->modelMatrix = modelMatrix; }
private:
	ModelData modelData;
	std::vector<MeshRenderData> renderMeshData;
	std::vector<Mesh> meshes;

	void GenBuffers();
	void BindVertexBuffers();
	void SetUniformData(size_t index);
	
	class ObjLoader* objLoader = nullptr;
	glm::mat4 modelMatrix;
};


