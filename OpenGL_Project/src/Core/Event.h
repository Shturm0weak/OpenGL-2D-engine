#ifndef EVENT_H_
#define EVENT_H_

class Listener;
class Event {
private:
	// Members
	const char* eventId;
	void* parameter;
	
public:
	Listener* sender;
	// Constructor
	Event(const char* eventId, Listener* sender, void* parameter = 0) {
		this->eventId = eventId;
		this->parameter = parameter;
		this->sender = sender;
	}

	char* GetNewRefOfEventId() {
		int size = 0;
		while (eventId[size] != '\0') {
			size++;
		}
		char* id = new char[size];
		for (int i = 0; i < size; i++) {
			id[i] = eventId[i];
		}
		id[size] = '\0';
		return id;
	}

	// Destructor
	~Event() {}

	// Accessors
	inline const char* EventId() const { 
		if(eventId != nullptr)
			return eventId;
		
	}
	inline void* Parameter() { return parameter; }
	inline Listener* Sender() { return sender; }
};

#endif // EVENT_H_