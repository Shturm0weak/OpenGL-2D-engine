#ifndef COMPONENT_H
#define COMPONENT_H

#include "IComponent.h"
class GameObject;

class Component : private IComponent {
private:
	int m_Id;
	const char* m_Type;
	Component* GetReference() { return this; }
protected:
	GameObject* owner = nullptr;
	virtual void SetType(const char* type) override{ m_Type = type; }
	virtual int GetComponentId() override{ return m_Id; }
	virtual const char* GetComponentType() override{ return m_Type; }
public:
	int GetComponentID() { return m_Id; }
	friend class ComponentManager;
};
#endif // !COMPONENT_H