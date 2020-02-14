#ifndef _EVENTSYSTEM_H_
#define _EVENTSYSTEM_H_

#include <list>
#include <map>
using std::multimap;
using std::list;
using std::pair;

#include "Event.h"
#include "Listener.h"
#include <iostream>
#include "ThreadPool.h"

class EventSystem {
private:
	
	// Database of Clients & their events
	multimap<const char*, Listener*> database;

	pair<multimap<const char*, Listener*>::iterator,
		multimap<const char*, Listener*>::iterator> range;

	multimap<const char*, Listener*>::iterator iter;
	// List of events to be processed
	std::queue<Event> currentEvents;
	std::list<Event> tempEvents;
	mutable std::mutex mtx,mtx1;
	std::condition_variable cond;
	bool process_events = false;
	// Helper Methods
	bool AlreadyRegistered(const char* eventId, Listener* client);
	void DispatchEvent(Event* event);

	// Singleton, deny access to constructors
	// Constructor
	EventSystem() {}
	// Copy constructor
	
	// Assignment Operator
	EventSystem& operator=(const EventSystem& rhs) { return *this; }

public:

	EventSystem(EventSystem& rhs) {}

	// Destructor
	~EventSystem() { this->Shutdown(); }

	// Returns an instance of the Event System
	static EventSystem* Instance();

	// Registers a client to start listening for an event
	void RegisterClient(const char* event, Listener* client);

	// Unregisters a client from a specific event
	void UnregisterClient(const char* event, Listener* client);

	// Unregister a client from all events
	void UnregisterAll(Listener* client);

	// Send an event
	void SendEvent(const char* eventId, Listener* sender,void* data = 0 );

	// Process all events
	void ProcessEvents();

	// Clear events
	void ClearEvents();

	// Shutdown event system
	void Shutdown();
};

#endif // _EVENTSYSTEM_H_