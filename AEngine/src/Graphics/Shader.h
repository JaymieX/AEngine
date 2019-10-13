#pragma once

class Shader
{
public:
	Shader(const char*, const char*);
   ~Shader();

	Shader(const Shader&)	= delete;
	Shader(Shader&&)		= delete;
	Shader& operator		= (const Shader&) = delete;
	Shader& operator		= (Shader&&) = delete;

	inline GLuint getProgram() const { return shaderID; }
	inline GLuint getUniformID(std::string name) { return uniforms[name]; }

private:
	char* ReadTextFile(const char*);
	void CompileShaderProgram(const char*, const char*);
	void LinkShaderProgram();

	void SetUniformLocations();

private:
	std::unordered_map<std::string, GLuint> uniforms;

	GLuint shaderID;
	GLuint vertShaderID;
	GLuint fragShaderID;
};