#pragma once

#include "../vendor/glm/glm.hpp"

class OrthographicCamera {
public:
	OrthographicCamera(float left,float right,float top,float bottom);

	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(const glm::vec3& position) { m_Position = position; }

	float GetRotation() const { return m_Rotation; }
	void SetRotation(float rotation) { m_Rotation = rotation; }

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	void RecalculateViewMatrix();
	void Increase(float deltatime);
	void Decrease(float deltatime);
	void Zoom(float zoomlevel);
private:
	float zoomlevel = 1.0f;
	glm::vec3 m_Position;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;
	float m_Rotation = 0.0f;
	float aspectration[4];


};
