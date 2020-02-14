#include "../pch.h"
#include "Editor.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

void Editor::EditorUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Editor", &tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::Button("Create a gameobject")) {
		Renderer::CreateGameObject();
		selected = Renderer2DLayer::GetAmountOfObjects() - 1;
	}
	ImGui::ListBox("Game objects", &selected, Renderer::GetItems(), Renderer::GetGameObjectAmount());
	GameObject* go = nullptr;
	if (Renderer2DLayer::GetAmountOfObjects() > 0) {
		go = static_cast<GameObject*>(Renderer::GetReference(selected));
		Transform* tr = go->component_manager->GetComponent<Transform>();
		Collision* col = go->component_manager->GetComponent<Collision>();
		ImGui::Text("ID %d", go->GetId());
		ImGui::Checkbox("Static", &go->Static);
		ImGui::InputText("Name",name, sizeof(name));
		ImGui::SameLine();
		if(ImGui::Button("Change name")) {
			go->SetName(name);
		}
		ImGui::SliderInt("Layer",&go->GetLayer(),0,Renderer2DLayer::GetAmountOfObjects() - 1);
		if (ImGui::Button("Change layer")) {
			if (go->GetLayer() > Renderer2DLayer::GetAmountOfObjects() - 1) {
				std::cout << red << "Error: layer out of range" << std::endl;
				return;
			}
			go->Setlayer(go->GetLayer());
			selected = go->GetId();
		}
		if (ImGui::Button("Delete selected gameobject")) {
			if (selected == Renderer2DLayer::GetAmountOfObjects() - 1)
				selected--;
			Renderer::DeleteObject(go->GetId());
		}
		ImGui::ListBox("Components objects", &selectedcomponent, go->GetComponentManager()->GetItems(), go->GetComponentManager()->GetAmountOfComponents());
		if(col == nullptr) {
			if (ImGui::Button("Add collision")) {
				go->GetComponentManager()->AddComponent<Collision>();
			}
		}
		if (selectedcomponent == 0) {
			ImGui::Text("Positions");
			ImGui::InputFloat2("Set the borders of X and Y position slider", changeSliderPos);
			ImGui::SliderFloat("Position X", &(tr->position.x), changeSliderPos[0], changeSliderPos[1]);
			ImGui::SliderFloat("Position Y", &(tr->position.y), changeSliderPos[0], changeSliderPos[1]);
			ImGui::InputFloat2("Positions", &(tr->position.x, tr->position.x));
			ImGui::Text("Scale");
			ImGui::InputFloat2("Set the borders of X and Y scale slider", changeSliderScale);
			ImGui::SliderFloat("Scale X", &(go->scaleinfo[0]), changeSliderScale[0], changeSliderScale[1]);
			ImGui::SliderFloat("Scale Y", &(go->scaleinfo[1]), changeSliderScale[0], changeSliderScale[1]);
			ImGui::InputFloat2("Scale", &(go->scaleinfo[0], go->scaleinfo[0]));
			ImGui::Text("Position: x: %lf y: %lf", go->GetPositions()[0], go->GetPositions()[1]);
			color = go->GetColor();
			ImGui::ColorEdit4("Color", color);
			tr->Scale(go->scaleinfo[0], go->scaleinfo[1]);
			tr->RotateOnce(tr->angle, glm::vec3(0, 0, 1));
			go->SetColor(glm::vec4(color[0], color[1], color[2], color[3]));
			delete[] color;
			for (unsigned int i = 0; i < texture.size(); i++)
			{
				void* my_tex_id = reinterpret_cast<void*>(texture[i]->m_RendererID);
				int frame_padding = -1;
				if (ImGui::ImageButton(my_tex_id, ImVec2(36, 36), ImVec2(0, 0), ImVec2(1, 1), frame_padding, ImVec4(1.0f, 1.0f, 1.0f, 0.5f))) {
					if (go != nullptr) {
						go->SetTexture(texturesPath[i]);
					}
				}
				ImGui::SameLine();
			}
			if (ImGui::Button("Refresh textures")) {
				for (unsigned int i = 0; i < texture.size(); i++)
				{
					texture[i]->~Texture();
				}
				texturesPath.clear();
				texture.clear();
				CheckTexturesFolder("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Images");
			}
			ImGui::SliderAngle("Rotate", &tr->angle);
		}
		else if (selectedcomponent == 1) {
			if (col != nullptr) {
				ImGui::Text("Collision");
				ImGui::Text("ID %d", col->GetId());
				ImGui::Text("Tag %s", col->GetTag().c_str());
				ImGui::Checkbox("Enable",&col->Enable);
				ImGui::Checkbox("Trigger", &col->IsTrigger);
				ImGui::Checkbox("Static", &col->Static);
				ImGui::InputFloat2("Set the borders of X and Y offset slider", changeSliderCollisionOffset);
				ImGui::SliderFloat("Offset X", &col->offsetX, changeSliderCollisionOffset[0], changeSliderCollisionOffset[1]);
				ImGui::SliderFloat("Offset Y", &col->offsetY, changeSliderCollisionOffset[0], changeSliderCollisionOffset[1]);
				ImGui::InputFloat2("Offset", &(col->offsetX, col->offsetX));
				col->SetOffset(col->offsetX, col->offsetY);
				if (ImGui::Button("Remove collision")) {
					go->component_manager->RemoveComponent<Collision>();
					selectedcomponent = 0;
				}
			}
		}			
		
		tr->Translate(tr->position.x, tr->position.y);
	}
	ImGui::Checkbox("See collisions", &Collision::IsVisible);
	ImGui::SliderFloat("Zoom", &zoomlevel, 0.1f, 25.f);
	Window::GetCamera().Zoom(abs(zoomlevel));
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::Button("Save")) {
		Renderer::Save("C:/Users/Alexandr/Desktop/saved.txt");
	}
	ImGui::SameLine();
	if (ImGui::Button("Load")) {
		selected = 0;
		Renderer::Load("C:/Users/Alexandr/Desktop/saved.txt");
	}
	ImGui::SameLine();
	if (ImGui::Button("EXIT")) {
		glfwSetWindowShouldClose(Window::GetWindow(), GLFW_TRUE);
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::CheckTexturesFolder(const std::string path)
{
	for (const auto & entry : fs::directory_iterator(path)) {
		texturesPath.push_back(entry.path().string());
		size_t index = 0;
		index = texturesPath.back().find("\\", index);
		texturesPath.back().replace(index, 1, "/");
		texture.push_back(new Texture(texturesPath.back(),0));
	}
}

Editor * Editor::Instance()
{
	static Editor instance;
	return &instance;
}
