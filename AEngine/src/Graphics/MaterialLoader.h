#pragma once

class MaterialLoader
{
public:
	static void LoadMaterial(const std::string& materialPath);
	static GLuint LoadMaterialTexture(const std::string& textureFileName);
};