#include "Basic2D.h"
#include <iostream>
#include "../Core/DeltaTime.h"
#include "../Core/ConsoleColor.h"

GLFWwindow *Window::m_window; //create the window
std::vector <std::reference_wrapper<Renderer>> Renderer::objects2d; //storage of all references to our 
																	//objects in the scene

Basic2D::Basic2D(float x,float y) {
	Renderer::PushObj(*this);
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
	Renderer::PushObj(*this);
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
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	this->shader->Bind();
	this->MVP = proj * scale * pos * view;
	this->shader->SetUniformMat4f("u_MVP", this->MVP);
	this->vb->Bind();
	if(ShaderType == SHADER)
		this->texture->Bind(this->texture->m_RendererID);
	Renderer::Draw(*this->va, *this->ib, *this->shader);
	this->shader->UnBind();
}

void Basic2D::Move(double speedx, double speedy) {
	double deltatime = DeltaTime::calculateDeltaTime();
	position.x += speedx * deltatime;
	position.y += speedy * deltatime;
	pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
}

void Basic2D::Rotate(float angle, glm::vec3 axis) {
	float deltatime = (float)DeltaTime::calculateDeltaTime();
	view = glm::rotate(view, angle * deltatime * 4.f, axis);
}
void Basic2D::Scale(float scale) {
	this->scale = glm::scale(this->scale,glm::vec3(scale,scale,0));
}

void Basic2D::SetTexture(const std::string& path) {
	if (this->texture != (void*)0xCCCCCCCC )
		delete(texture);
	texture = new Texture(path);
}

void Basic2D::InitShader() {
	if (texture == (void*)0xCCCCCCCC && ShaderType == SHADER) {
		std::cout << yellow << "InitShader" << " : " << red << "Texture doesn't exist!" << std::endl;
		ShaderType = COLOR;
	}
		if (shader != (void*)0xCCCCCCCC) {
			shader->UnBind();
			delete(shader);
		}
		if (ShaderType == SHADER) {
			shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/Basic.shader");
		}
		else if (ShaderType == COLOR) {
			shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/newshader.shader");
		}
		shader->Bind();
		if (ShaderType == SHADER) {
			this->texture->Bind(this->texture->m_RendererID);
			this->shader->SetUniform1i("u_Texture", this->texture->m_RendererID);
		}
}

void Basic2D::SetShader(int _enum) {
	if (_enum == 1) {
		ShaderType = COLOR;
		if (this->texture != (void*)0xCCCCCCCC ) {
			delete texture;
		}
		InitShader();
	}
	else if (_enum == 0) {
		ShaderType = SHADER;
		InitShader();
	}
}

