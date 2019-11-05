#pragma once
class GameObject;

class Component {
private:
	int m_Id;
	const char* m_Type;
	Component* GetReference() { return this; }
protected:
	void SetType(const char* type) { m_Type = type; }
	inline int GetComponentId() { return m_Id; }
	const char* GetComponentType() { return m_Type; }
public:
	GameObject* owner = nullptr;
	friend class ComponentManager;
};