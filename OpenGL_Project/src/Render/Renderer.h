#ifndef RENDERER_H
#define RENDERER_H

#include "../Render/Renderer2D.h"
#include "../Components/Collision.h"
#include "../Core/Editor.h"
#include "../ECS/ComponentManager.h"
#include <mutex>

class Renderer{
public:
	static void DeleteObject(int id);
	static void DeleteAll();
	static void Render(OrthographicCamera& camera);
	static void Clear();
	static void Save(const std::string filename);
	static void Load(const std::string filename);
	static int GetGameObjectAmount() { return Renderer2DLayer::objects2d.size(); }
	static Renderer2DLayer* GetReference(int id) { return &Renderer2DLayer::objects2d[id].get(); }
	static const char** items;

	static const char** GetItems() {
		delete[] items;
		items = new const char*[Renderer2DLayer::objects2d.size()];
		for (unsigned int i = 0; i < Renderer2DLayer::objects2d.size(); i++)
		{
			items[i] = new char[sizeof(*Renderer2DLayer::objects2d[i].get().name->c_str())/sizeof(const char)];
			items[i] = Renderer2DLayer::objects2d[i].get().name->c_str();
		}
		return items;
	}

	static void CreateGameObject() {
		GameObject * go = new GameObject();
	}
private:

	Renderer() {}
	
	template<typename T>
	static void LoadObj(std::string name,std::string pathtotext,float angle, float color[4], float scale[3], double pos[2],int shadertype,bool hascollision,float* offset) {
		T* go = new T(name, pos[0], pos[1]);
		go->GetComponentManager()->GetComponent<Transform>()->Scale(scale[0], scale[1]);
		go->GetComponentManager()->GetComponent<Transform>()->RotateOnce(angle, glm::vec3(0, 0, 1));
		if (shadertype == 1)
			go->SetColor(glm::vec4(color[0], color[1], color[2], color[3]));
		else if (shadertype == 0) {
			go->SetColor(glm::vec4(color[0], color[1], color[2], color[3]));
			go->SetTexture(pathtotext);
		}
		if (hascollision == 1) {
			go->GetComponentManager()->AddComponent<Collision>();
			go->GetComponentManager()->GetComponent<Collision>()->Translate(pos[0],pos[1]);
			go->GetComponentManager()->GetComponent<Collision>()->Enable = true;
			go->GetComponentManager()->GetComponent<Collision>()->SetOffset(offset[0],offset[1]);
			go->GetComponentManager()->GetComponent<Transform>()->Scale(scale[0], scale[1]);
		}
	}

};
#endif