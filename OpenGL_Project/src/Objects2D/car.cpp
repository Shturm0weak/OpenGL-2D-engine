#include "car.h"
#include <iostream>

Car2D::Car2D(float speed, glm::mat4 pos, float angle, Renderer& renderer) {
	renderer.objects2d.push_back(*this);
	this->speed = this->defspeed = speed;
	this->pos = pos;
	this->angle = angle;

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	this->layout->Push<float>(2);
	this->layout->Push<float>(2);
	this->va->AddBuffer(*this->vb, *this->layout);
	this->shader->Bind();
	this->texture->Bind(this->texture->m_RendererID);
	this->shader->SetUniform1i("u_Texture", this->texture->m_RendererID);
	this->va->UnBind();
	this->shader->UnBind();
	this->vb->UnBind();
	this->ib->UnBind();
}

void Car2D::OnRunning(glm::mat4 proj, Renderer& renderer, double deltatime) {
	if (collide) {
		angle = PI - angle;
		speed = defspeed;
		std::cout << 180 / PI * angle << std::endl;
		collide = false;
	}
	this->shader->Bind();
	this->pos = translate(pos, glm::vec3(speed * cos(angle) * deltatime, speed * sin(angle) * deltatime, 0));
	this->MVP = proj * view * pos;
	this->shader->SetUniformMat4f("u_MVP", this->MVP);
	this->vb->Bind();
	this->texture->Bind(this->texture->m_RendererID);
	renderer.Draw(*this->va, *this->ib, *this->shader);
	this->shader->UnBind();
}
