#pragma once

#include "Systems/EntityComponent.h"

class Shader : public Component
{
public:
	Shader() = default;
	Shader(const char*, const char*, const char*);
	
   ~Shader();
	
	void Start() override;
	void Render() override;
	
private:
	static GLuint CreateShader(const GLenum, const char*, const char*);
	
	const char* shaderName; 
	const char* vertFilePath;
	const char* fragFilePath; 

	GLuint programId;
};