#include "../pch.h"
#include "GameObject.h"
#include <thread>

GameObject::GameObject(std::string name,float x,float y) {
	this->name = name;
	component_manager = new ComponentManager(this,this->name);
	component_manager->AddComponent<Transform>();
	Renderer2DLayer::PushObj(*this);
	position.x = x;
	position.y = y;
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	this->layout->Push<float>(2);
	this->layout->Push<float>(2);
	this->va->AddBuffer(*this->vb, *this->layout);
	InitShader();
	this->va->UnBind();
	this->shader->UnBind();
	this->vb->UnBind();
	this->ib->UnBind();
}
GameObject::GameObject() {
	component_manager = new ComponentManager(this,this->name);
	this->name = "unnamed";
	component_manager->AddComponent<Transform>();
	Renderer2DLayer::PushObj(*this);
	position.x = 0;
	position.y = 0;
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	this->layout->Push<float>(2);
	this->layout->Push<float>(2);
	this->va->AddBuffer(*this->vb, *this->layout);
	InitShader();
	this->va->UnBind();
	this->shader->UnBind();
	this->vb->UnBind();
	this->ib->UnBind();

}

void GameObject::OnRunning(glm::mat4 proj) {
	this->shader->Bind();
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	this->viewXscale = scale * view;
	this->MVP = proj * pos * viewXscale;
	this->shader->SetUniformMat4f("u_MVP", this->MVP);
	if (ShaderType == SHADER_TEXTURE)
		this->texture->Bind(this->texture->m_RendererID);
	Renderer2DLayer::Draw(*this->va, *this->ib, *this->shader);
}


void GameObject::SetTexture(const std::string& path) {
	if (this->texture != (void*)0xCCCCCCCC || this->texture != nullptr) {
		delete(texture);
		texture = nullptr;
	}
	texture = new Texture(path);
	SetShader(GameObject::SHADER_TEXTURE);
}

void GameObject::InitShader() {
	if (texture == (void*)0xCCCCCCCC && ShaderType == SHADER_TEXTURE || texture == nullptr && ShaderType == SHADER_TEXTURE) {
		std::cout << yellow << "InitShader" << " : " << red << "Texture doesn't exist!" << white << std::endl;
		ShaderType = SHADER_COLOR;
	}
	if (shader != (void*)0xCCCCCCCC || shader != nullptr) {
		shader->UnBind();
		delete(shader);
		shader = nullptr;
	}
	if (ShaderType == SHADER_TEXTURE) {
		shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/Basic.shader");
		shader->Bind();
		this->texture->Bind(this->texture->m_RendererID);
		this->shader->SetUniform1i("u_Texture", this->texture->m_RendererID);
	}
	else if (ShaderType == SHADER_COLOR) {
		shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/newshader.shader");
		shader->Bind();
		shader->SetUniform4fv("U_Color",this->color);
	}
}

void GameObject::SetShader(int _enum) {
	if (_enum == 1) {
		ShaderType = SHADER_COLOR;
		if (this->texture != (void*)0xCCCCCCCC && this->texture != nullptr) {
			delete texture;
			texture = nullptr;
		}
		InitShader();
	}
	else if (_enum == 0) {
		ShaderType = SHADER_TEXTURE;
		InitShader();
	}
}

void GameObject::SetColor(vec4 color) {
	this->color = color;
	SetShader(GameObject::SHADER_COLOR);
}