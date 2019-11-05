#include "../pch.h"
#include "Collision.h"
#include "../Objects2D/Basic2D.h"
Collision::Collision(double x, double y) {
	SetType("Collision");
	Renderer2DLayer::PushCol(*this);
	position.x = x;
	position.y = y;
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	RealVerPos();
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	this->layout->Push<float>(2);
	this->layout->Push<float>(2);
	this->va->AddBuffer(*this->vb, *this->layout);
	shader->Bind();
	shader->SetUniform4fv("U_Color", this->Color);
	this->va->UnBind();
	this->shader->UnBind();
	this->vb->UnBind();
	this->ib->UnBind();
}
Collision::Collision() {
	SetType("Collision");
	Renderer2DLayer::PushCol(*this);
	position.x = 0;
	position.y = 0;
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	RealVerPos();
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	this->layout->Push<float>(2);
	this->layout->Push<float>(2);
	this->va->AddBuffer(*this->vb, *this->layout);
	shader->Bind();
	shader->SetUniform4fv("U_Color", this->Color);
	this->va->UnBind();
	this->shader->UnBind();
	this->vb->UnBind();
	this->ib->UnBind();
}

void Collision::UpdateCollision(double x, double y,glm::mat4 pos,glm::mat4 view,glm::mat4 scale)
{
	this->scale = scale;
	this->view = view;
	if (scaleXview != view * scale) {
		this->scaleXview = view * scale;
		RealVerPos();
	}	
	this->pos = pos;
	this->position.x = x + offsetX;
	this->position.y = y + offsetY;	
}

void Collision::OnRunning(glm::mat4 proj)
{
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	this->shader->Bind();
	this->MVP = proj * pos * scaleXview;
	this->shader->SetUniformMat4f("u_MVP", this->MVP);
	Renderer2DLayer::Draw(*this->va, *this->ib, *this->shader);
}
void Collision::RealVerPos() {
	float* pSource;
	pSource = (float*)glm::value_ptr(this->scaleXview);
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			ScaledVerPos[i * 4 + j] = 0;
			for (unsigned int k = 0; k < 4; k++) {
				ScaledVerPos[i * 4 + j] += positions[i * 4 + k] * pSource[k * 4 + j];
			}
		}
	}
	pSource = nullptr;
}

float* Collision::GetVertexPositions() {
	return ScaledVerPos;
}

void Collision::Scale(float x,float y) {
	if (this == nullptr) 
		return;
	this->scale = glm::scale(glm::mat4(1.f), glm::vec3(x, y, 0));
	RealVerPos();
	UpdateCollision(position.x, position.y, pos, view, this->scale);
}

void Collision::SetOffset(float x, float y) {
	offsetX = x;
	offsetY = y;
	position.x += offsetX;
	position.y += offsetY;
}

bool Collision::IsCollided() {
	if (this == nullptr)
		return false;
	if (Enable == true) {
		Collided_side_right = false;
		Collided_side_left = false;
		Collided_side_top = false;
		Collided_side_bottom = false;
	
		for (unsigned int i = 0; i < collision2d.size(); i++)
		{
			if (collision2d[i].get().IsCollisionEnabled() == true) {
				if (this != &collision2d[i].get()) {
					col = dynamic_cast<Collision*>(collision2d[i].get().GetCollisionReference());
					arrver1 = col->GetVertexPositions();
					arrpos1 = col->GetPositions();

					if (GetDistance(position.x, position.y, arrpos1[0], arrpos1[1] < 1.1 * (arrver1[4] + ScaledVerPos[4]))) {
						right = ScaledVerPos[8] + position.x;
						left = ScaledVerPos[0] + position.x;
						top = ScaledVerPos[13] + position.y;
						bottom = ScaledVerPos[1] + position.y;
						col->right = arrver1[8] + arrpos1[0];
						col->left = arrver1[0] + arrpos1[0];
						col->top = arrver1[13] + arrpos1[1];
						col->bottom = arrver1[1] + arrpos1[1];
						difftb = abs(top) - abs(col->bottom);
						diffbt = abs(bottom) - abs(col->top);
						diffrl = abs(right) - abs(col->left);
						difflr = abs(left) - abs(col->right);
						if (right > col->left &&
							left < col->right &&
							bottom < col->top &&
							top > col->bottom) {

							if (diffbt < 0.2 && diffbt > -0.2) {
								Collided_side_bottom = true;
							}
							else if (difftb < 0.2 && difftb > -0.2) {
								Collided_side_top = true;
							}
							else if (diffrl < 0.2 && diffrl > -0.2) {
								Collided_side_right = true;
							}
							else if (difflr < 0.2 && difflr > -0.2) {
								Collided_side_left = true;
							}
						}
						delete[] arrpos1;
						arrpos1 = nullptr;
						col = nullptr;
					}
				}
			}
		}
		if (Collided_side_bottom || Collided_side_left || Collided_side_right || Collided_side_top)
			return true;
		else
			return false;
	}
	else {
		return false;
	}
}