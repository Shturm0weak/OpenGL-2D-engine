#include "../pch.h"
#include "Transform.h"

Transform::Transform() {
	SetType("Transform");
}

void Transform::init() {
	position.x = owner->position.x;
	position.y = owner->position.y;
}

void Transform::Move(float speedX,float speedY) {
	position.x += speedX * DeltaTime::deltatime;
	position.y += speedY * DeltaTime::deltatime;
	owner->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	col = owner->component_manager->GetComponent<Collision>();
	if (col != nullptr)
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
	owner->position.x = position.x;
	owner->position.y = position.y;
}

void Transform::Rotate(float angle, glm::vec3 axis) {
	float deltatime = (float)DeltaTime::deltatime;
	owner->view = glm::rotate(owner->view, angle * deltatime * 4.f, axis);
	col = owner->component_manager->GetComponent<Collision>();
	if (col != nullptr)
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
}
void Transform::Scale(float scaleX, float scaleY) {
	owner->scale = glm::scale(glm::mat4(1.f), glm::vec3(scaleX, scaleY, 0));
	col = owner->component_manager->GetComponent<Collision>();
	if (col != nullptr)
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
}

void Transform::Translate(float x, float y)
{
	position.x = x;
	position.y = y;
	owner->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	col = owner->component_manager->GetComponent<Collision>();
	if (col != nullptr)
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
	owner->position.x = position.x;
	owner->position.y = position.y;
}
