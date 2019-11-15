#pragma once

class Model
{
public:
	Model() = default;
   ~Model() = default;
	
	explicit Model(class EntityManager*, std::string, std::string, GLuint);

	void CreateSubModel(glm::vec3 pos, float angle, glm::vec3 rotationAxis, glm::vec3 scale);
	void UpdateSubModel(int index, glm::vec3 pos, float angle, glm::vec3 rotationAxis, glm::vec3 scale);
	glm::mat4 GetModelMatrix(int index); 
	
private:
	class Entity* modelEntityPtr;
	class Transform* transformComponentPtr;
	class Mesh* meshComponentPtr;
	class MeshRenderer* meshRendererComponent;

	std::vector<glm::mat4> submodels;
};