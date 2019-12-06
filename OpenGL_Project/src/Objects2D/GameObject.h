#pragma once
#ifndef BASIC2D_H
#define BASIC2D_H

#include "../Render/Renderer2D.h"
#include "../ECS/ComponentManager.h"
#include "../Core/Listener.h"
#include "../Core/Event.h"

class GameObject : public Renderer2DLayer,public Listener
{
public:
	enum shaderE { SHADER_TEXTURE, SHADER_COLOR };
	ComponentManager* component_manager;
private:
	shaderE ShaderType = SHADER_COLOR;
	struct Position {
		double x = 0;
		double y = 0;
	};
	
	void InitShader();
	virtual void OnRunning(glm::mat4 proj) override;
	virtual Renderer2DLayer* GetCollisionReference() override{ return component_manager->GetComponent<Collision>(); }
	const unsigned int indeces[6] = { 0,1,2,3,2,0 };
	const float positions[16] = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f
	};

protected:
	glm::mat4 scale = glm::mat4(1.f);
	glm::mat4 pos = glm::mat4(1.f);
	glm::mat4 viewXscale = glm::mat4(1.f);
	glm::mat4 MVP = glm::mat4(1.f);
	glm::mat4 view = glm::mat4(1.f);

	Position position;
private:

	GLuint vao;
	VertexBufferLayout* layout = new VertexBufferLayout;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexArray* va = new VertexArray;
	IndexBuffer* ib = new IndexBuffer(indeces, 6);
	Texture* texture = nullptr;
	Shader* shader = nullptr;
	friend class Transform;
public:	
	glm::vec4 color = COLORS::White;
	using Renderer2DLayer::name;
	explicit GameObject(std::string name,float x,float y);
	explicit GameObject();
	void SetTexture(const std::string& path);
	void SetColor(vec4 color);
	void SetShader(int _enum);
};
#endif 

