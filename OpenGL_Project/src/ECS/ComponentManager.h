#pragma once
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "../Objects2D/GameObject.h"
#include "../Render/Renderer2D.h"
#include "Component.h"
#include "../Components/Collision.h"
#include "../Components/Transform.h"

class ComponentManager {
	GameObject* owner = nullptr;
	std::string owner_name;
	int maxComponents = 32;
	int currentLength = 0;
	std::vector <std::reference_wrapper<Component>> components;
	void pushcomponents(Component& obj) { components.push_back(obj); }
public:
	ComponentManager(GameObject* owner, std::string& owner_name) {
		this->owner = owner;
		this->owner_name = owner_name;
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
		}
		std::cout << yellow << "Warning:" << white << " there is no component of type <Collision> for gameobject: " << owner_name << std::endl;
		return nullptr;
	}

	template<>
	Transform* GetComponent() {
		for (unsigned int i = 0; i < components.size(); i++)
		{
			if (components[i].get().GetComponentType() == "Transform") {
				return (Transform*)components[i].get().GetReference();
			}
		}
		std::cout << yellow << "Warning:" << white << " there is no component of this type <Transform> for gameobject: " << owner_name << std::endl;
		return nullptr;
	}

	template<class T>
	T* AddComponent() {

	}

	template <>
	Collision* AddComponent<Collision>() {
		if (currentLength >= maxComponents) {
			return nullptr;
		}
		else {
			Collision* object = new Collision();
			object->owner = owner;
			currentLength++;
			object->m_Id = currentLength;
			pushcomponents(*object);
			return object;
		}
	}

	template <>
	Transform* AddComponent<Transform>() {
		if (currentLength >= maxComponents) {
			return nullptr;
		}
		else {
			Transform* object = new Transform();
			object->owner = owner;
			object->init();
			currentLength++;
			object->m_Id = currentLength;
			pushcomponents(*object);
			return object;
		}
	}
};
#endif
