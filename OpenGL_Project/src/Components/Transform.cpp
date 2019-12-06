#include "../pch.h"
#include "Transform.h"
#include "../Core/EventSystem.h"
Transform::Transform() {
	SetType("Transform");
	
}

void Transform::init() {
	position.x = owner->position.x;
	position.y = owner->position.y;
	
}

void Transform::Move(float speedX,float speedY,float speedZ) {
	position.x += speedX * DeltaTime::deltatime;
	position.y += speedY * DeltaTime::deltatime;
	position.z += speedZ * DeltaTime::deltatime;
	owner->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, position.z));
	if (col == nullptr) {
		col = owner->component_manager->GetComponent<Collision>();
	}
	if (col != nullptr) {
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
	}
	owner->position.x = position.x;
	owner->position.y = position.y;
	EventSystem::Instance()->SendEvent("OnMove",(Listener*)owner);
}

void Transform::Rotate(float angle, glm::vec3 axis) {
	float deltatime = (float)DeltaTime::deltatime;
	owner->view = glm::rotate(owner->view, angle * deltatime * 4.f, axis);
	if (col == nullptr) {
		col = owner->component_manager->GetComponent<Collision>();
	}
	if (col != nullptr)
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
	EventSystem::Instance()->SendEvent("OnRotate",(Listener*)owner);
}
void Transform::Scale(float scaleX, float scaleY) {
	owner->scale = glm::scale(glm::mat4(1.f), glm::vec3(scaleX, scaleY, 0));
	if (col == nullptr) {
		col = owner->component_manager->GetComponent<Collision>();
	}
	if (col != nullptr)
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
	EventSystem::Instance()->SendEvent("OnScale",(Listener*)owner);
}

void Transform::Translate(float x, float y)
{
	position.x = x;
	position.y = y;
	owner->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, position.z));
	if (col == nullptr) {
		col = owner->component_manager->GetComponent<Collision>();
	}
	if (col != nullptr)
		col->UpdateCollision(position.x, position.y, owner->pos, owner->view, owner->scale);
	owner->position.x = position.x;
	owner->position.y = position.y;
}
