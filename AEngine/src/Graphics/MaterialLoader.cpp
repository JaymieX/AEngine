#include <Core/AEpch.h>
#include "MaterialLoader.h"
#include "MaterialHandler.h"
#include "TextureHandler.h"
#include "Core/Logger.h"

void MaterialLoader::LoadMaterial(const std::string& materialPath)
{
	std::ifstream in(materialPath.c_str(), std::ios::in);
	if (!in) {
		LOG_ERROR("Could not open MTL file: " + materialPath, "MaterialLoader.cpp", __LINE__);
		return;
	}
	auto m = MaterialHandler::Material();
	auto matName = std::string();
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(matName, m);
				m = MaterialHandler::Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadMaterialTexture(line.substr(7));
		}
		if (line.substr(0, 3) == "\tNs") {
			double n;
			std::istringstream s(line.substr(3));
			s >> n;
			m.roughness = n;
		}
		if (line.substr(0, 2) == "\td") {
			double n;
			std::istringstream s(line.substr(2));
			s >> n;
			m.transparency = n;
		}
		if (line.substr(0, 3) == "\tKa") {
			glm::vec3 ambient;
			double x, y, z;
			std::istringstream v(line.substr(3));
			v >> x >> y >> z;
			ambient = glm::vec3(x, y, z);
			m.ambientColor = ambient;
		}
		if (line.substr(0, 3) == "\tKd") {
			glm::vec3 diffuse;
			double x, y, z;
			std::istringstream v(line.substr(3));
			v >> x >> y >> z;
			diffuse = glm::vec3(x, y, z);
			m.diffuseColor = diffuse;
		}
		if (line.substr(0, 3) == "\tKs") {
			glm::vec3 specular;
			double x, y, z;
			std::istringstream v(line.substr(3));
			v >> x >> y >> z;
			specular = glm::vec3(x, y, z);
			m.specularColor = specular;
		}
	}
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(matName, m);
	}
}

GLuint MaterialLoader::LoadMaterialTexture(const std::string& textureFileName)
{
	auto currentTexture = TextureHandler::GetInstance()->GetTextureId(textureFileName);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(textureFileName, "src/Resources/Textures/" + textureFileName + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTextureId(textureFileName);
	}
	return currentTexture;
}
