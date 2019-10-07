#include "glew.h"
#include "glfw3.h"
#include "../Core/Core.h"
#include "../Render/Shader.h"
#include "../Render/Renderer.h"
#include "../Render/VertexArray.h"
#include "../Render/IndexBuffer.h"
#include "../Render/VertexBuffer.h"
#include "../Render/Texture.h"
#pragma once

class Triangle2D : public Renderer {
public:
	const unsigned int indecestwo[3] = { 0,1,2 };
	const int scale = 10;
	const float positionstri[12] = {
		-0.5f * scale, -0.5f * scale, 0.0f, 0.0f,
		 0.5f * scale, -0.5f * scale, 1.0f, 0.0f,
		 0.5f * scale,  0.5f * scale, 1.0f, 1.0f, };
	float speed, defspeed;
	double angle = 0;
	glm::mat4 pos;
	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 MVP;
	GLuint vao;
	VertexBuffer* vb = new VertexBuffer(positionstri, 4 * 3 * sizeof(float));
	Shader* shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/Basic.shader");
	VertexBufferLayout* layout = new VertexBufferLayout;
	VertexArray* va = new VertexArray;
	IndexBuffer* ib = new IndexBuffer(indecestwo, 3);
	Texture* texture = new Texture("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Images/one.png");

	Triangle2D(float speed, glm::mat4 pos, float angle, Renderer& renderer);

	void OnRunning(glm::mat4 proj, Renderer& renderer, double deltatime);

	inline glm::mat4& GetMVP() { return MVP; }
	inline void SetSpeed(float _speed) { speed = _speed; }
	inline float GetSpeed() { return defspeed; }
	inline void SetAngle(double _angle) { angle = _angle; }
	inline double GetAngle() { return angle; }
};