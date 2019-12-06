#include <Core/AEpch.h>
#include "Core/Utils.h"
#include "Core/Logger.h"
#include "Shader.h"

std::unique_ptr<ShaderHandler> ShaderHandler::instance(nullptr);
std::map<const char*, GLuint> ShaderHandler::programs = std::map<const char*, GLuint>();

ShaderHandler* ShaderHandler::GetInstance() {
	if (!instance) instance = std::unique_ptr<ShaderHandler>(new ShaderHandler());
	return instance.get();
}

ShaderHandler::~ShaderHandler()
{
	//if (!programs.empty()){
	//	for (const auto& entry : programs) glDeleteProgram(entry.second);
	//	programs.clear();
	//}
}

GLuint ShaderHandler::GetShaderProgram(const char* shaderName)
{
	if (programs.find(shaderName) != programs.end()) {
		return programs.at(shaderName);
	}
	return 0;
}

void ShaderHandler::CreateProgram(const char* shaderName, const char* vertFilePath, const char* fragFilePath)
{
	auto vShaderCode = Utils::ReadTextFile(vertFilePath);
	auto fShaderCode = Utils::ReadTextFile(fragFilePath);

	const auto vertShaderId = CreateShader(GL_VERTEX_SHADER, vShaderCode, shaderName);
	const auto fragShaderId = CreateShader(GL_FRAGMENT_SHADER, fShaderCode, shaderName);

	GLint linkResult;
	const auto programId = glCreateProgram();

	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &linkResult);

	if (!linkResult)
	{
		char log[512];
		glGetProgramInfoLog(programId, 512, nullptr, &log[0]);
		LOG_ERROR("Error linking ShaderHandler Program: " + std::string(shaderName) + ". Error: \n" + log, __FILE__, __LINE__);
	}

	programs.emplace(std::make_pair(shaderName, programId));
	
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);
}

GLuint ShaderHandler::CreateShader(const GLenum shaderType, std::string& shaderSource, const char* shaderName)
{
	auto compileResult = 0;
	const auto shader = glCreateShader(shaderType);

	const auto shaderCode = shaderSource.c_str();

	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (!compileResult)
	{
		auto logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> shaderLog(logLength);
		glGetShaderInfoLog(shader, logLength, nullptr, &shaderLog[0]);
		const std::string logString(shaderLog.begin(), shaderLog.end());
		LOG_ERROR("Error compiling shader " + std::string(shaderName) + ". Error: \n" + logString, __FILE__, __LINE__);
		return 0;
	}

	return shader;
}




