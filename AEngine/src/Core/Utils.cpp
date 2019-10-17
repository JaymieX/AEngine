#include <Core/AEpch.h>
#include "Core/Logger.h"
#include "Utils.h"

const char* Utils::ReadTextFile(const char* path)
{
	const char* buffer = nullptr;
	std::ifstream file;
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try
	{
		file.open(path);
		std::stringstream stream;

		stream << file.rdbuf();
		file.close();
		buffer = stream.str().c_str();
	}
	catch (std::ifstream::failure ifStreamException)
	{
		LOG_ERROR("Could not read shader file: " + std::string(path), __FILE__, __LINE__);
		return "";
	}

	return buffer;
}
