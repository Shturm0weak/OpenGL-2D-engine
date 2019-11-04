#include "../pch.h"
#include "Basic2D.h"

Basic2D::Basic2D(std::string name,float x,float y) {
	ComponentsManager = new ComponentManager(this);
	this->name = name;
	Renderer2D::PushObj(*this);
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
Basic2D::Basic2D() {
	ComponentsManager = new ComponentManager(this);
	this->name = "unnamed";
	Renderer2D::PushObj(*this);
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

void Basic2D::OnRunning(glm::mat4 proj) {
	this->shader->Bind();
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	this->viewXscale = scale * view;
	this->MVP = proj * pos * viewXscale;
	this->shader->SetUniformMat4f("u_MVP", this->MVP);
	if(ShaderType == SHADER_TEXTURE)
		this->texture->Bind(this->texture->m_RendererID);
	Renderer2D::Draw(*this->va, *this->ib, *this->shader);
}


void Basic2D::SetTexture(const std::string& path) {
	if (this->texture != (void*)0xCCCCCCCC || this->texture != nullptr) {
		delete(texture);
		texture = nullptr;
	}
	texture = new Texture(path);
}

void Basic2D::InitShader() {
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
		shader->SetUniform4fv("U_Color",this->Color);
	}
}

void Basic2D::SetShader(int _enum) {
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

void Basic2D::SetColor(vec4 color) {
	this->Color = color;
}