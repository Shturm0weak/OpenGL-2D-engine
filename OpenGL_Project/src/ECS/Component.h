#pragma once
class Basic2D;

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
	Basic2D* owner = nullptr;
	friend class ComponentManager;
};