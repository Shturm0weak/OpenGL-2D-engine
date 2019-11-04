#pragma once
#include "../ECS/Component.h"
class Transform : public Component {
public:
	Transform() {
		SetType("Transform");
	}
	void Move(float speedY, float speedX);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(float scaleX,float scaleY);
};