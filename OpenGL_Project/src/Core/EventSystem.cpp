#include "EventSystem.h"
#include <memory>
#include "../Core/ConsoleColor.h"


bool EventSystem::AlreadyRegistered(const char* eventId, Listener* client) {
	// Assume they are not already registered
	bool alreadyRegistered = false;

	// Range iterator
	pair<multimap<const char*, Listener*>::iterator,
		multimap<const char*, Listener*>::iterator> range;

	// Find all the clients able to receive this event
	range = database.equal_range(eventId);

	
	// Go through the list of clients
	for (multimap<const char*, Listener*>::iterator iter = range.first;
		iter != range.second; iter++) {
		// If this client is already subscribed
		if ((*iter).second == client) {
			// Already registered, quit now
			alreadyRegistered = true;
			break;
		}
	}

	return alreadyRegistered;
}

void EventSystem::DispatchEvent(Event* _event) {
	// Get all the clients who respond to this event
	range = database.equal_range(_event->EventId());
	// For every client

	for (iter = range.first;
		iter != range.second; iter++) {
		//Event* e = new Event(_event->EventId(), _event->Sender());
		//std::function<void()> f1 = std::bind(&Listener::HandleEvent, (*iter).second,e);
		//ThreadPool::thread_pool->enqueue(f1);
			(*iter).second->HandleEvent(_event);
			if ((std::string)_event->EventId() != "OnUpdate") {
				return;
			}
	}	
}

// Returns an instance of the Event System
EventSystem* EventSystem::Instance() {
	static EventSystem instance;
	return &instance;
}

// Registers a client to start listening for an event
void EventSystem::RegisterClient(const char* event, Listener* client) {
	// If the client is null, or already registered
	if (!client || AlreadyRegistered(event, client)) {
		// Quit now

		return;
	}

	// Insert the client into the database
	database.insert(std::make_pair(event, client));
}

// Unregisters a client from a specific event
void EventSystem::UnregisterClient(const char* event, Listener* client) {
	// Iterator
	pair<multimap<const char*, Listener*>::iterator,
		multimap<const char*, Listener*>::iterator> range;

	//  Find all the clients able to receive this event
	range = database.equal_range(event);

	// For every client who can respond to this event
	for (multimap<const char*, Listener*>::iterator iter = range.first;
		iter != range.second; iter++) {
		// If this is the guy we remove
		if ((*iter).second == client) {
			// Erase the bastard & quit
			iter = database.erase(iter);
			break;
		}
	}
}

// Unregister a client from all events
void EventSystem::UnregisterAll(Listener* client) {
	if (database.size() > 0) {
		// Iterator
		multimap<const char*, Listener*>::iterator iter = database.begin();
		// For every entry in the database
		while (iter != database.end()) {
			// If this is the chosen one
			if ((*iter).second == client) {
				// Destroy him
				iter = database.erase(iter);
			}
			else {
				// Move on
				iter++;
			}
		}
	}
}

void EventSystem::SendEvent(const char* eventId, Listener* sender, void* data)
{

	std::unique_ptr<Event> newEvent(new Event(eventId, sender, data));
	//std::lock_guard<std::mutex> lck(mtx);
	currentEvents.push(*newEvent);
	//cond.notify_one();
	//std::cout << currentEvents.size() << std::endl;
}

// Process all events
void EventSystem::ProcessEvents() {
	//std::unique_lock<std::mutex> lck(mtx);
	//cond.wait(lck);
	while (currentEvents.size() > 0) {
		Event newEvent = currentEvents.front();
		currentEvents.pop();
		DispatchEvent(&newEvent);
		//std::cout << currentEvents.front().EventId() << std::endl;
	}
	//lck.unlock();
}

// Clear events
void EventSystem::ClearEvents() {
	// Clear the events
	
	while (currentEvents.size() > 0) {
		currentEvents.pop();
	}
}

// Shutdown event system
void EventSystem::Shutdown() {
	database.clear();
	ClearEvents();
}