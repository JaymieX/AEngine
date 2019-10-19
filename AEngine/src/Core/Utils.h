#pragma once

#include "Graphics/Mesh.h"

class Utils
{
public:
	static std::string ReadTextFile(const char*);

	class LoadOBJModel
	{
	public:
		LoadOBJModel() = default;
		~LoadOBJModel();

		void LoadModel(const std::string& fileName);
		void LoadModel(const std::string& fileName, const std::string & matName);

		std::vector<Vertex> GetVerts();
		std::vector<int> GetIndices();
		std::vector<Mesh> GetSubmeshes();

	private:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;
		std::vector<glm::vec2> indices;
		std::vector<glm::vec2> normalIndicies;
		std::vector<glm::vec2> textureIndicies;
		std::vector<glm::vec2> meshVertices;
		std::vector<glm::vec2> subMeshes;

		void PostProcessing();
		void LoadMaterial(const std::string& fileName);
		void LoadMaterialLibrary(const std::string& matName);

		GLuint currentTexture;

	};
};