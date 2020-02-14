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
	virtual void OnCollision(void* col) {}
	
protected:
	virtual ~Listener() {}
	
public:
	Listener() {}

	void HandleEvent(Event* e) {
		std::string s = e->EventId();
		if (s == "OnUpdate")
			OnUpdate();
		else if (s == "OnStart")
			OnStart();
		else if (s == "OnCollision")
			e->Sender()->OnCollision(e->Parameter());
		else if (s == "OnMove")
			e->Sender()->OnMove();
		else if (s == "OnRotate")
			e->Sender()->OnRotate();
		else if (s == "OnScale")
			e->Sender()->OnScale();
	}
};

#endif // LISTENER_H_