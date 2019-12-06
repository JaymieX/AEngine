#include <Core/AEpch.h>
#include "MaterialHandler.h"

std::unique_ptr<MaterialHandler> MaterialHandler::instance(nullptr);
std::map<std::string, MaterialHandler::Material> MaterialHandler::materials = std::map<std::string, MaterialHandler::Material>();

MaterialHandler* MaterialHandler::GetInstance()
{
	if(!instance) instance = std::unique_ptr<MaterialHandler>(new MaterialHandler());
	return instance.get();
}

void MaterialHandler::AddMaterial(std::string materialName, Material material)
{
	if(materials.find(materialName) != materials.end()) return;
	materials.emplace(std::make_pair(materialName, material));
}

MaterialHandler::Material MaterialHandler::GetMaterial(const std::string materialName)
{
	const auto it = materials.find(materialName);
	if(it != materials.end())
		return it->second;
	return Material();
}

void MaterialHandler::Clear()
{
	materials.clear();
}

MaterialHandler::~MaterialHandler()
{
	//Clear();
}
