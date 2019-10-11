#pragma once

class Shader;
class Model;

using namespace glm;
class GameObject
{
public:
	GameObject(Model*, Shader*);
	~GameObject();

	void Render() const;
	void Update(float);

	inline Shader* getShader() const { return shader; }
	inline mat4& getModelMatrix() { return transform; }
	inline void setModelMatrix(const mat4& transform) { this->transform = transform; }

private:
	mat4 transform;
	Model* model;
	Shader* shader;
};