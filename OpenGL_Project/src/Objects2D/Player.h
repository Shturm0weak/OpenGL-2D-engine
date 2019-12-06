#include <iostream>
#include "../Core/ThreadPool.h"
class Player : public GameObject {
public:
	std::mutex mtx;
	Collision* collision = nullptr;
	Transform* transform = nullptr;
	bool IsColorOn = false;
	double scale = 1;
	double weight = 2;
	double speed = 0;
	Player(std::string name,float x,float y) : GameObject(name,x,y){
		transform = component_manager->GetComponent<Transform>();
		component_manager->AddComponent<Collision>();
		collision = component_manager->GetComponent<Collision>();
		EventSystem::Instance()->RegisterClient("OnCollision", this);
		EventSystem::Instance()->RegisterClient("OnMove", this);
		EventSystem::Instance()->RegisterClient("OnRotate", this);
		EventSystem::Instance()->RegisterClient("OnScale", this);
		EventSystem::Instance()->RegisterClient("OnUpdate", this);
		EventSystem::Instance()->RegisterClient("OnStart", this);
	}

	Player() : GameObject("unnamed", 0, 0) {
		transform = component_manager->GetComponent<Transform>();
		component_manager->AddComponent<Collision>();
		collision = component_manager->GetComponent<Collision>();
		EventSystem::Instance()->RegisterClient("OnCollision", this);
		EventSystem::Instance()->RegisterClient("OnMove", this);
		EventSystem::Instance()->RegisterClient("OnRotate", this);
		EventSystem::Instance()->RegisterClient("OnScale", this);
		EventSystem::Instance()->RegisterClient("OnUpdate", this);
		EventSystem::Instance()->RegisterClient("OnStart", this);
	}

	void MOVE(float speedx, float speedy) {
		if (collision->IsCollided()) {
			if (collision->Collided_side_bottom && speedy < 0)
				speedy = 0;
			if (collision->Collided_side_top && speedy > 0)
				speedy = 0;
			if (collision->Collided_side_right && speedx > 0)
				speedx = 0;
			if (collision->Collided_side_left && speedx < 0)
				speedx = 0;
			EventSystem::Instance()->SendEvent("OnCollision", this, nullptr);
		}
		transform->Move(speedx, speedy, 0);
		
	}

	void OnUpdate(){
		speed -= 9.8 * weight;
		if (speed < -9.8*weight)
			speed = -9.8 * weight;
		MOVE(3, speed);
	}

	void OnCollision() {
		transform->Translate(-20, 0);
	}
	
	void Impulse(double Force) {
		speed = Force;
	}
};