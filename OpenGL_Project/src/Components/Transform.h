#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../ECS/Component.h"

class Transform : public Component {
private:

	Collision* col = nullptr;
	struct Position {
		float x = 0;
		float y = 0;
		float z = 0;
	};
	void init();
	friend class ComponentManager;

public:
	Transform();
	Position position;
	float angle = 0;
	void Move(float speedY, float speedX,float speedZ);
	void Rotate(float angle, glm::vec3 axis);
	void Scale(float scaleX,float scaleY);
	void Translate(float x,float y);
	void RotateOnce(float angle, glm::vec3 axis);
};
#endif