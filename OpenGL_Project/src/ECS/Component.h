#pragma once
#include "IComponent.h"
class GameObject;

class Component : private IComponent {
private:
	int m_Id;
	const char* m_Type;
	Component* GetReference() { return this; }
protected:
	virtual void SetType(const char* type) override{ m_Type = type; }
	virtual int GetComponentId() override{ return m_Id; }
	virtual const char* GetComponentType() override{ return m_Type; }
public:
	GameObject* owner = nullptr;
	friend class ComponentManager;
};