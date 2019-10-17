#pragma once

class Shader;
class Model;

using namespace glm;
class GameObject
{
public:
	GameObject() = default;
	GameObject(Model*, Shader*);
	~GameObject();

	void Render() const;
	void Update(float);

	inline Shader* getShader() const { return shader; }
	inline mat4& getModelMatrix() { return transformMatrix; }
	inline void setModelMatrix(const mat4& transform) { this->transformMatrix = transform; }

private:
	GLuint transformMatrixID, normalMatrixID;
	mat4 transformMatrix;
	Model* model;
	Shader* shader;
};