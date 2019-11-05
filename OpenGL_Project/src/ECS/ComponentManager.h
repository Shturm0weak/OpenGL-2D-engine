#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "../Render/Renderer2D.h"
#include "Component.h"
#include "../Core/Collision.h"
#include "../Components/Transform.h"

class GameObject;

class ComponentManager {
	GameObject* owner = nullptr;
	int maxComponents = 32;
	int currentLength = 0;
	std::vector <std::reference_wrapper<Component>> components;
	void pushcomponents(Component& obj) { components.push_back(obj); }
public:
	ComponentManager(GameObject* owner) {
		this->owner = owner;
	}

	template <class T >
	T* GetComponent() {
		return nullptr;
	}	

	template<>
	Collision* GetComponent() {
		for (unsigned int i = 0; i < components.size(); i++)
		{

			if (components[i].get().GetComponentType() == "Collision") {
				return (Collision*)components[i].get().GetReference();
			}
			else {
				std::cout << "Error: there is no component of this type" << std::endl;
				return nullptr;
			}
		}
	}

	template<>
	Transform* GetComponent() {
		for (unsigned int i = 0; i < components.size(); i++)
		{

			if (components[i].get().GetComponentType() == "Transform") {
				return (Transform*)components[i].get().GetReference();
			}
		}
		std::cout << "Error: there is no component of this type" << std::endl;
		return nullptr;
	}

	template<class T>
	void AddComponent() {

	}

	template <>
	void AddComponent<Collision>() {
		if (currentLength >= maxComponents) {
			return;
		}
		else {
			Collision* object = new Collision();
			object->owner = owner;
			currentLength++;
			object->m_Id = currentLength;
			pushcomponents(*object);
		}
	}

	template <>
	void AddComponent<Transform>() {
		if (currentLength >= maxComponents) {
			return;
		}
		else {
			Transform* object = new Transform();
			object->owner = owner;
			object->init();
			currentLength++;
			object->m_Id = currentLength;
			pushcomponents(*object);
		}
	}
};
#endif
