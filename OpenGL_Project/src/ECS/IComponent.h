#ifndef ICOMPONENT_H
#define ICOMPONENT_H

class IComponent {
protected:
	virtual void SetType(const char* type) = 0;
	virtual int GetComponentId() = 0;
	virtual const char* GetComponentType() = 0;
};
#endif
