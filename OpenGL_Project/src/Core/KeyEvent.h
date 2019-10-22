#pragma once
#include "Event.h"

class KeyEvent : public Event {
public:
	inline int GetKeyCode() const { return m_KeyCode; }

	int GetCategoryFlags() { return EventCategory::EventCategoryInput; }
protected:
	KeyEvent(int keycode):m_KeyCode(keycode) {
	}
	int m_KeyCode;
};