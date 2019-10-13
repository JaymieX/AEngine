#pragma once

using namespace glm;

struct Vertex {
	vec3 position;
	vec3 normals;
	vec3 color;
	vec2 uvCoords;
};

class Mesh
{
public:
	Mesh(GLenum, std::vector<Vertex*>&);
   ~Mesh();

	void Render() const;

private:
	void GenBuffers();

public:
	GLenum drawmode;
	std::vector<Vertex*> verticies;
	std::vector<GLuint> indices;

private:
	GLuint vao, vbo;
};