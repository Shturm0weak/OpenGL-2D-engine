#ifndef BASIC2D_H
#define BASIC2D_H

#include "../Render/Renderer2D.h"
#include "../ECS/ComponentManager.h"

class Basic2D : public Renderer2D
{
public:
	enum shaderE { SHADER_TEXTURE, SHADER_COLOR };
	ComponentManager* ComponentsManager;
private:
	shaderE ShaderType = SHADER_COLOR;
	struct Position {
		double x = 0;
		double y = 0;
	};
	
	void InitShader();
	virtual void OnRunning(glm::mat4 proj) override;
	virtual Renderer2D* GetCollisionReference() override{ return ComponentsManager->GetComponent<Collision>(); }

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
	
	glm::vec4 Color = COLORS::White;
	using Renderer2D::name;
	explicit Basic2D(std::string name,float x,float y);
	explicit Basic2D();
	void SetTexture(const std::string& path);
	void SetColor(vec4 color);
	void SetShader(int _enum);
	Position position;
};
#endif 

