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


class Basic2D : public Renderer
{
public:
	Basic2D(float x,float y);
	Basic2D();
	void Move(double speedx,double speedy);
	void Rotate(float angle,glm::vec3 axis);
	void Scale(float scale);
	void SetTexture(const std::string& path);
	enum shaderE { SHADER, COLOR };
	void SetShader(int _enum);

private:
	struct Position {
		double x = 0;
		double y = 0;
	};
	virtual void OnRunning(glm::mat4 proj) override;
	void InitShader();
	void Clear() {};
	void Render() {};
public:
	Position position;

private:
	shaderE ShaderType = COLOR;
	const unsigned int indeces[6] = { 0,1,2,3,2,0 };
	const float positions[16] = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f
	};	glm::mat4 scale = glm::mat4(1.f);
	glm::mat4 pos = glm::mat4(1.f);
	glm::mat4 MVP = glm::mat4(1.f);
	glm::mat4 view = glm::mat4(1.f);
	GLuint vao;
	VertexBufferLayout* layout = new VertexBufferLayout;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexArray* va = new VertexArray;
	IndexBuffer* ib = new IndexBuffer(indeces, 6);	
	Texture* texture;
	Shader* shader;
};

