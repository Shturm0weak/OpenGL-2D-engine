#ifndef EDITOR_H
#define EDITOR_H
#include "../vendor/ImGUI/imgui.h"
#include "../vendor/ImGUI/imgui_impl_glfw.h"
#include "../vendor/ImGUI/imgui_impl_opengl3.h"
#include "../Render/Renderer.h"
#include <mutex>

class Editor {
private:
	bool tool_active = true;
	int selected = 0;
	int selectedcomponent = 0;
	float* color;
	float changeSliderPos[2] = {-10,10};
	float changeSliderScale[2] = { 0,10 };
	float changeSliderCollisionOffset[2] = { -10,10 };
	float zoomlevel = 1;
	char name[128];
	float colOffset[2] = { 0,0 };
	static std::vector<std::string> texturesPath;
	static std::vector<Texture*> texture;
	Editor& operator=(const Editor& rhs) { return *this; }
	Editor() {}
public:
	static Editor* Instance();
	void EditorUpdate();
	static void CheckTexturesFolder(const std::string path);
};
#endif