#include "../pch.h"
#include "Transform.h"

void Transform::Move(float speedX,float speedY) {
	owner->position.x += speedX * DeltaTime::deltatime;
	owner->position.y += speedY * DeltaTime::deltatime;
	owner->pos = translate(glm::mat4(1.f), glm::vec3(owner->position.x, owner->position.y, 0));
	Collision* col = nullptr;
	col = owner->ComponentsManager->GetComponent<Collision>();
	if (col != nullptr)
		col->UpdateCollision(owner->position.x, owner->position.y, owner->pos, owner->view, owner->scale);
}

void Transform::Rotate(float angle, glm::vec3 axis) {
	float deltatime = (float)DeltaTime::deltatime;
	owner->view = glm::rotate(owner->view, angle * deltatime * 4.f, axis);
	Collision* col = nullptr;
	col = owner->ComponentsManager->GetComponent<Collision>();
	if (col != nullptr)
		col->UpdateCollision(owner->position.x, owner->position.y, owner->pos, owner->view, owner->scale);
}
void Transform::Scale(float scaleX, float scaleY) {
	owner->scale = glm::scale(glm::mat4(1.f), glm::vec3(scaleX, scaleY, 0));
	Collision* col = nullptr;
	col = owner->ComponentsManager->GetComponent<Collision>();
	if (col != nullptr)
		col->UpdateCollision(owner->position.x, owner->position.y, owner->pos, owner->view, owner->scale);
}