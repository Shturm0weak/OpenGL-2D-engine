#include "pch.h"

#include "Core/Core.h"
#include "Core//Event.h"
#include "Core/Input.h"
#include "Core/KeyCode.h"

#include "Render/Renderer.h"
#include "Render/Renderer2D.h"

#include "ECS/Component.h"
#include "ECS/ComponentManager.h"

#include "Core/EventSystem.h"

#include "Components/Collision.h"
#include "Components/Transform.h"

#include "Core/ThreadPool.h"
#include "Core/AllStatics.h"
#include "Core/Editor.h"
#include <random>
#include <fstream>
using namespace std;

void CameraMovement() {
	if (Input::IsKeyPressed(Keycode::KEY_UP)) {
		glm::vec3 pos = Window::GetCamera().GetPosition();
		Window::GetCamera().SetPosition(glm::vec3(pos.x, pos.y + (10 * DeltaTime::deltatime), 0));
	}
	if (Input::IsKeyPressed(Keycode::KEY_DOWN)) {
		glm::vec3 pos = Window::GetCamera().GetPosition();
		Window::GetCamera().SetPosition(glm::vec3(pos.x, pos.y - (10 * DeltaTime::deltatime), 0));
	}
	if (Input::IsKeyPressed(Keycode::KEY_RIGHT)) {
		glm::vec3 pos = Window::GetCamera().GetPosition();
		Window::GetCamera().SetPosition(glm::vec3(pos.x + (10 * DeltaTime::deltatime), pos.y, 0));
	}
	if (Input::IsKeyPressed(Keycode::KEY_LEFT)) {
		glm::vec3 pos = Window::GetCamera().GetPosition();
		Window::GetCamera().SetPosition(glm::vec3(pos.x - (10 * DeltaTime::deltatime), pos.y, 0));
	}

}

int main(void)
{
	{
		Window::Init(); //инициализация окна
		ThreadPool::Init();
		GameObject* go = new GameObject();
		Renderer::Load("C:/Users/Alexandr/Desktop/saved.txt");
		Editor::Instance()->CheckTexturesFolder("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Images");
		EventSystem::Instance()->SendEvent("OnStart", nullptr);
		while (!glfwWindowShouldClose(Window::GetWindow())) {
			EventSystem::Instance()->SendEvent("OnUpdate", nullptr);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			DeltaTime::calculateDeltaTime();
			Renderer::Render(Window::GetCamera());
			Editor::Instance()->EditorUpdate();
			CameraMovement();
			glfwSwapBuffers(Window::GetWindow());
			
			glfwPollEvents();
			EventSystem::Instance()->ProcessEvents();
		}
	}

	EventSystem::Instance()->Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	
	ThreadPool::Instance()->shutdown();
	return 0;
}