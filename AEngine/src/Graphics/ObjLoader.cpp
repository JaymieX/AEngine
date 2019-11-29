#include <Core/AEpch.h>
#include "ObjLoader.h"
#include "Core/Logger.h"
#include "TextureHandler.h"

ObjLoader::~ObjLoader()
{
	vertices.clear();
	normals.clear();
	uvCoords.clear();
	indices.clear();
	normalIndices.clear();
	uvIndices.clear();
	meshVertices.clear();
	meshes.clear();
}

void ObjLoader::LoadMeshData(const std::string& fileName)
{
	std::ifstream in(fileName, std::ios::in);
	if (!in) {
		LOG_ERROR("Cannot open OBJ file: " + fileName, "ObjLoader.cpp", __LINE__);
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		// Order: Vert Tex Normal
		// VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			glm::vec3 vert;
			double x, y, z;
			std::istringstream v(line.substr(2));
			v >> x >> y >> z;
			vert = glm::vec3(x, y, z);
			vertices.push_back(vert);
			//std::cout << "V " << x << ", " << y << ", " << z << std::endl;
		}
		// NORMAL DATA
		if (line.substr(0, 2) == "vn") {
			glm::vec3 normal;
			double x, y, z;
			std::istringstream v(line.substr(2));
			v >> x >> y >> z;
			normal = glm::vec3(x, y, z);
			normals.push_back(normal);
			//std::cout << "VN " << x << ", " << y << ", " << z << std::endl;
		}
		// TEXUTRE DATA
		if (line.substr(0, 2) == "vt") {
			glm::vec2 textureCoord;
			double x, y;
			std::istringstream v(line.substr(2));
			v >> x >> y;
			textureCoord = glm::vec2(x, y);
			uvCoords.push_back(textureCoord);
			//std::cout << "VT " << x << ", " << y << std::endl;
		}
		// FACE DATA
		if (line.substr(0, 1) == "f") {
			unsigned int x[3], y[3], z[3];
			char s;
			std::istringstream v(line.substr(2));
			v >> x[0] >> s >> y[0] >> s >> z[0] >> x[1] >> s >> y[1] >> s >> z[1] >> x[2] >> s >> y[2] >> s >> z[2];
			for (int i = 0; i < 3; i++) {
				indices.push_back(x[i]);
				uvIndices.push_back(y[i]);
				normalIndices.push_back(z[i]);
			}
		}

		// NEW MATERIAL
		else if (line.substr(0, 7) == "usemtl ") {
			if (!indices.empty()) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void ObjLoader::LoadMeshData(const std::string& fileName, const std::string& matName)
{
	LoadMaterialLibrary(matName);
	LoadMeshData(fileName);
}

void ObjLoader::PostProcessing()
{
	for (auto i = 0; i < indices.size(); i++) {
		Vertex vert{};
		vert.position = vertices[indices[i] - 1]; std::cout << i << ":" << glm::to_string(vert.position) << std::endl;
		vert.normal = normals[normalIndices[i] - 1];
		vert.uvCoords = uvCoords[uvIndices[i] - 1];
		meshVertices.push_back(vert);
	}
	Mesh mesh;
	mesh.vertices = meshVertices;
	mesh.indices = indices;
	mesh.textureId = currentTexture;
	meshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	uvIndices.clear();

	currentTexture = 0;
}

void ObjLoader::LoadMaterial(const std::string& fileName)
{
	currentTexture = TextureHandler::GetInstance()->GetTextureId(fileName);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName, "src/Resources/Textures/" + fileName + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTextureId(fileName);
	}
}

void ObjLoader::LoadMaterialLibrary(const std::string& matName)
{
	std::ifstream in(matName.c_str(), std::ios::in);
	if (!in) {
		LOG_ERROR("Could not open MTL file: " + matName, "ObjLoader.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl") {
			LoadMaterial(line.substr(7));
		}
	}
}
