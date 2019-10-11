#include <AEpch.h>
#include "Shader.h"

Shader::Shader(const char* vert, const char* frag)
{
	CompileShaderProgram(vert, frag);
	LinkShaderProgram();
	SetUniformLocations();
}

Shader::~Shader()
{
	glDetachShader(shaderID, fragShaderID);
	glDetachShader(shaderID, vertShaderID);
	glDeleteShader(fragShaderID);
	glDeleteShader(vertShaderID);
	glDeleteProgram(shaderID);
}

char* Shader::ReadTextFile(const char* path)
{
	std::ifstream file(path, std::ios::binary);
}

void Shader::CompileShaderProgram(const char* vert, const char* frag)
{

}

void Shader::LinkShaderProgram()
{

}

void Shader::SetUniformLocations()
{

}

