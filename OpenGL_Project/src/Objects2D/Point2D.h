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

class Point2D : public Renderer
{
public:
	const float scale = 1.f;
	const unsigned int indeces[6] = { 0,1,2,3,2,0 };
	const float positions[16] = {
	-0.5f * scale, -0.5f * scale, 0.0f, 0.0f,
	 0.5f * scale, -0.5f * scale, 1.0f, 0.0f,
	 0.5f * scale,  0.5f * scale, 1.0f, 1.0f,
	-0.5f * scale,  0.5f * scale, 0.0f, 1.0f
	};
	float speed, defspeed;
	double angle;
	glm::mat4 pos;
	glm::mat4 MVP;
	glm::mat4 view = glm::mat4(1.f);
	GLuint vao;
	VertexBufferLayout* layout = new VertexBufferLayout;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexArray* va = new VertexArray;
	Shader* shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/Basic.shader");
	IndexBuffer* ib = new IndexBuffer(indeces, 6);
	Texture* texture = new Texture("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Images/reddot.png");

	Point2D(float speed,glm::mat4 pos ,float angle,Renderer& renderer);
	virtual void OnRunning(glm::mat4 proj, Renderer& renderer, double deltatime) override;

	inline glm::mat4& GetMVP() { return MVP; }
	inline glm::mat4& GetNormals() { glm::mat4 m = glm::transpose(glm::inverse(MVP)); return m; }
	inline void SetSpeed(float _speed) { speed = _speed; }
	inline float GetSpeed() { return defspeed; }
	inline void SetAngle(double _angle) { angle = _angle; }
	inline double GetAngle () { return angle; }
};

