#pragma once

#include <Core/AEpch.h>
#include "BoundingBox.h"
#include "CollisionDetection.h"
#include "Graphics/Shader.h"

struct Ray
{
	Ray() = default;
	Ray(const glm::vec3 origin, const glm::vec3 direction, const glm::vec2 dimensions) :
		origin(origin), direction(direction), dimensions(dimensions) { }
	Ray(const Ray& otherRay) { origin = otherRay.origin; direction = otherRay.direction; dimensions = otherRay.dimensions; }
	Ray& operator=(const Ray& otherRay) { origin = otherRay.origin; direction = otherRay.direction; dimensions = otherRay.dimensions; return *this; }

	bool IsColliding(BoundingBox* boundingBox)
	{
		intersection = -1.0f;
		return CollisionDetection::RayCastHit(*this, boundingBox);
	}

	void Render(Camera* cameraPtr) const
	{
		glm::vec2 points[2];
		points[0] = origin;
		points[1] = origin + direction * dimensions.y;
		
		const auto program = ShaderHandler::GetInstance()->GetShaderProgram("BasicShader");
		glUseProgram(program);
		
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(cameraPtr->GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(cameraPtr->GetPerspectiveMatrix()));
		
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2, &points[0], GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3, static_cast<GLvoid*>(nullptr));
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_LINE, 0, static_cast<GLsizei>(2));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
	
	glm::vec3 origin = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f);
	glm::vec2 dimensions = glm::vec3(0.0f);
	float intersection = 0;
};