#include <Core/AEpch.h>
#include "Core/Logger.h"
#include "Utils.h"

std::string Utils::ReadTextFile(const char* path)
{
	std::string shaderString;
	std::ifstream file;
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		file.open(path);
		std::stringstream stream;

		stream << file.rdbuf();
		file.close();
		shaderString = stream.str();
	}
	catch (std::ifstream::failure ifStreamException)
	{
		LOG_ERROR("Could not read shader file: " + std::string(path), __FILE__, __LINE__);
		return "";
	}

	return shaderString;
}

Utils::LoadOBJModel::~LoadOBJModel()
{
}

void Utils::LoadOBJModel::LoadModel(const std::string& fileName)
{
}

void Utils::LoadOBJModel::LoadModel(const std::string& fileName, const std::string& matName)
{
}

std::vector<Vertex> Utils::LoadOBJModel::GetVerts()
{
	return std::vector<Vertex>();
}

std::vector<int> Utils::LoadOBJModel::GetIndices()
{
	return std::vector<int>();
}

std::vector<Mesh> Utils::LoadOBJModel::GetSubmeshes()
{
	return std::vector<Mesh>();
}

void Utils::LoadOBJModel::PostProcessing()
{
}

void Utils::LoadOBJModel::LoadMaterial(const std::string& fileName)
{
}

void Utils::LoadOBJModel::LoadMaterialLibrary(const std::string& matName)
{
}
