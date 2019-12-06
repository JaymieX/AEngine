#pragma once

class ShaderHandler
{
public:
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();
	GLuint GetShaderProgram(const char*);
	void CreateProgram(const char*, const char*, const char*);
	void Destroy();
	
private:
	ShaderHandler() = default;
   ~ShaderHandler();

	static std::unique_ptr<ShaderHandler> instance;
	friend std::default_delete<ShaderHandler>;
	static std::map<const char*, GLuint> programs;
	static GLuint CreateShader(GLenum, std::string&, const char*);
};
