#pragma once
#include "Systems/EntityComponent.h"
#include "Mesh.h"

struct ModelData
{
	const char* shaderName;
	const char* vertShaderPath;
	const char* fragShaderPath;
	std::string objPath;
	std::string materialPath;
	Entity* cameraEntity;
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(glm::vec4(0.0f));
};

class Model final : public Component
{
public:
	explicit Model(ModelData&);
	~Model();

	void Start() override;
	void Render() override;
	void Render(size_t index);

	[[nodiscard]] std::vector<Mesh> GetMeshes() const { return meshes; }
private:
	ModelData modelData;
	std::vector<MeshRenderData> renderMeshData;
	std::vector<Mesh> meshes;

	void GenBuffers();
	void BindVertexBuffers();
	void SetUniformData(size_t index);
	
	class Transform* transformPtr = nullptr;
	class ObjLoader* objLoader = nullptr;
};


