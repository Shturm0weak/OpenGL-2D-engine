#pragma once
#include "../ECS/Component.h"

class Transform : public Component {
private:


	Collision* col = nullptr;
	struct Position {
		double x = 0;
		double y = 0;
	};
	void init();
	friend class ComponentManager;
public:

	Position position;
	Transform();
	void Move(float speedY, float speedX);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(float scaleX,float scaleY);
	void Translate(float x,float y);
};