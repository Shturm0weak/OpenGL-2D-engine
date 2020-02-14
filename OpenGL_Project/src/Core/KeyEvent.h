#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "Event.h"

class KeyEvent : public Event {
public:
	inline int GetKeyCode() const { return m_KeyCode; }

	int GetCategoryFlags() { return Eventcategory::EventCategoryInput; }
protected:
	KeyEvent(int keycode):m_KeyCode(keycode) {
	}
	int m_KeyCode;
};
#endif // !