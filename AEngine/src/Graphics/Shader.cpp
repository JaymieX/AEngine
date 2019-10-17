#include <Core/AEpch.h>
#include "Shader.h"
#include "Core/Utils.h"
#include "Core/Logger.h"

Shader::Shader(const char* name, const char* vert, const char* frag) :
	shaderName(name), vertFilePath(vert),
	fragFilePath(frag), programId(0)
	{ }

Shader::~Shader()
{
	glDeleteProgram(programId);
}

void Shader::Start()
{
	const auto vShaderCode = Utils::ReadTextFile(vertFilePath);
	const auto fShaderCode = Utils::ReadTextFile(fragFilePath);

	const auto vertShaderId = CreateShader(GL_VERTEX_SHADER, vShaderCode, shaderName);
	const auto fragShaderId = CreateShader(GL_FRAGMENT_SHADER, fShaderCode, shaderName);

	GLint linkResult;
	programId = glCreateProgram();

	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &linkResult);

	if(!linkResult)
	{
		char log[512];
		glGetProgramInfoLog(programId, 512, nullptr, &log[0]);
		LOG_ERROR("Error linking Shader Program: " + std::string(shaderName) + ". Error: \n" + log, __FILE__, __LINE__);
	}

	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);
}

void Shader::Render()
{
	glUseProgram(programId);
}

GLuint Shader::CreateShader(const GLenum shaderType, const char* shaderSource, const char* shaderName)
{
	auto compileResult = 0;
	const auto shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if(!compileResult)
	{
		GLint logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> shaderLog(logLength);
		glGetShaderInfoLog(shader, logLength, nullptr, &shaderLog[0]);
		const std::string logString(shaderLog.begin(), shaderLog.end());
		LOG_ERROR("Error compiling shader " + std::string(shaderName) + ". Error: \n" + logString, __FILE__, __LINE__);
		return 0;
	}

	return shader;
}




