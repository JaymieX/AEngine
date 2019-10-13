#include <Core/AEpch.h>
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
	char* buffer = nullptr;

	std::ifstream file(path, std::ios::binary);

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		int bufferSize = (int)file.tellg();

		if (bufferSize == 0 )
		{
			std::string errorMsg("Can't read shader file: ");
			std::string str2(path);
			errorMsg += str2;
			throw errorMsg;
		}

		buffer = new char[(int)(bufferSize + 1)];
		file.seekg(0, std::ios::beg);
		file.read(buffer, bufferSize);
		buffer[bufferSize] = '\0';
		file.close();
	}
	else 
	{
		std::string errorMsg("Can't open shader file: ");
		std::cout << &errorMsg << ":" << path << std::endl;
	}
	return buffer;
}

void Shader::CompileShaderProgram(const char* vert, const char* frag)
{
	GLint status;
	shaderID = 0;
	vertShaderID = 0;
	fragShaderID = 0;

	try {
		const char* vsText = ReadTextFile(vert);
		const char* fsText = ReadTextFile(frag);
		if (vsText == NULL || fsText == NULL) return;

		/// GL_VERTEX_SHADER and GL_FRAGMENT_SHADER are defined in glew.h
		vertShaderID = glCreateShader(GL_VERTEX_SHADER);
		fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		
		/// Check for errors
		if (vertShaderID == 0 || fragShaderID == 0) {
			std::string errorMsg("Can't create a new shader");
			throw errorMsg;
		}

		glShaderSource(vertShaderID, 1, &vsText, 0);
		glShaderSource(fragShaderID, 1, &fsText, 0);

		glCompileShader(vertShaderID);
		/// Check for errors
		glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			GLsizei titleLength;
			std::string errorLog = "VERT:\n";
			titleLength = errorLog.length();
			glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(titleLength + errorLogSize);
			glGetShaderInfoLog(vertShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
			throw errorLog;
		}

		glCompileShader(fragShaderID);
		/// Check for errors
		glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			GLsizei titleLength;
			std::string errorLog = "FRAG:\n";
			titleLength = errorLog.length();
			glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(titleLength + errorLogSize);
			glGetShaderInfoLog(fragShaderID, errorLogSize, &errorLogSize, &errorLog[titleLength]);
			throw errorLog;
		}

		shaderID = glCreateProgram();
		glAttachShader(shaderID, fragShaderID);
		glAttachShader(shaderID, vertShaderID);
		if (vsText) delete[] vsText;
		if (fsText) delete[] fsText;
	}
	catch (std::string error) {
		printf("%s\n", &error[0]);
	}
}

void Shader::LinkShaderProgram()
{
	GLint status;
	try {
		glLinkProgram(shaderID);
		/// Check for errors
		glGetProgramiv(shaderID, GL_LINK_STATUS, &status);
		if (status == 0) {
			GLsizei errorLogSize = 0;
			std::string errorLog;
			glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &errorLogSize);
			errorLog.resize(errorLogSize);
			glGetProgramInfoLog(shaderID, errorLogSize, &errorLogSize, &errorLog[0]);
			throw errorLog;
		}

	}
	catch (std::string error) {
		printf("ERROR:%s\n", &error[0]);
	}
}

void Shader::SetUniformLocations()
{
	int count;
	GLsizei actualLen;
	GLint size;
	GLenum type;
	char* name;
	int maxUniLength;
	unsigned int loc;

	glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &count);
	printf("There are %d active Uniforms\n", count);

	/// get the length of the longest named uniform 
	glGetProgramiv(shaderID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniLength);

	/// Create a little buffer to hold the uniform's name - old C memory call just for fun 
	name = (char*)malloc(sizeof(char) * maxUniLength);


	for (int i = 0; i < count; ++i) {
		/// Get the name of the ith uniform
		glGetActiveUniform(shaderID, i, maxUniLength, &actualLen, &size, &type, name);
		/// Get the (unsigned int) loc for this uniform
		loc = glGetUniformLocation(shaderID, name);
		std::string uniformName = name;
		uniforms[uniformName] = loc;

		printf("\"%s\" loc:%d\n", uniformName.c_str(), uniforms[uniformName]);
	}
	free(name);
}

