#pragma once

class MaterialHandler
{
public:
	struct Material
	{
		GLuint diffuseMap = 0;
		float roughness = 0.0f;
		float transparency = 0.0f;
		glm::vec3 ambientColor = glm::vec3(1.0f);
		glm::vec3 diffuseColor = glm::vec3(1.0f);
		glm::vec3 specularColor = glm::vec3(1.0f);
	};
	
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator=(const MaterialHandler&) = delete;
	MaterialHandler& operator=(MaterialHandler&&) = delete;

	static MaterialHandler* GetInstance();

	void AddMaterial(std::string, Material);
	Material GetMaterial(std::string);
	void Clear();

private:
	MaterialHandler() = default;
   ~MaterialHandler();

	static std::map<std::string, Material> materials;

	static std::unique_ptr<MaterialHandler> instance;
	friend std::default_delete<MaterialHandler>;
};