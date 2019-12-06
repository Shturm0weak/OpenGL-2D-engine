#ifndef LISTENER_H_
#define LISTENER_H_
#include <iostream>
#include "Event.h"
#include <string>
#include "ThreadPool.h"

class Listener {
private:
	virtual void OnUpdate(){}
	virtual void OnMove() {}
	virtual void OnRotate() {}
	virtual void OnStart() {}
	virtual void OnScale() {}
	virtual void OnCollision() {}

public:
	// Constructor
	Listener() {}
	// Destructor
	virtual ~Listener() {}
	// Handles the event passed to it
	void HandleEvent(Event* e) {
		std::string s = e->EventId();
		if (s == "OnUpdate")
			OnUpdate();
		else if (s == "OnStart")
			OnStart();
		else if (s == "OnCollision")
			e->Sender()->OnCollision();
		else if (s == "OnMove")
			e->Sender()->OnMove();
		else if (s == "OnRotate")
			e->Sender()->OnRotate();
		else if (s == "OnScale")
			e->Sender()->OnScale();	
	}
};

#endif // LISTENER_H_