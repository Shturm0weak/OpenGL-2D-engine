class Player : public GameObject {
public:

	Collision* collision = nullptr;
	Transform* transform = nullptr;
	
	explicit Player(std::string name,float x,float y) : GameObject(name,x,y){
		component_manager->AddComponent<Collision>();
		collision = component_manager->GetComponent<Collision>();
		component_manager->AddComponent<Transform>();
		transform = component_manager->GetComponent<Transform>();
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
		}
			transform->Move(speedx, speedy);
	}
};