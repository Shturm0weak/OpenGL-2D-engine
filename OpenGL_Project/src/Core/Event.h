#pragma once

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){ return EventType::##type;} \
								virtual EventType GetEventType() const override { return GetStaticType(); }


enum class EventType {
	None = 0,
	WindowClosed, CollisionHit, RenderTick, RenderUpdate,
	MouseEvent, KeyEvent
 };

enum EventCategory {
	EventCategoryInput = BIT(0),
	EventCategoryMouse = BIT(1)
};

class Event {
	friend class EventDispatcher;
public:
	virtual EventType GetEventType()const = 0;
	virtual int GetCategory() const = 0;
	virtual int GetCategoryFlags() const = 0;

	bool IsInCategory(EventCategory category) {
		return GetCategoryFlags() &category;
	}
protected:
	bool m_Handled = false;
};

/*class EventDispatcher {
public:
	template<typename T>
	using EventFn = std::function<bool(T&)>;
	EventDispatcher(Event& event) : m_Event(event) {}

	template<typename T>
	bool Dispatch(EventFn<T> func) {
		if (m_Event.GetEventType() == T::GetStaticType()) {
			m_Event.m_Handled = func(*(T*)&m_Event);
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};*/