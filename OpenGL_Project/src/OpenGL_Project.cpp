#include "pch.h"

#include "vendor/ImGUI/imgui.h"
#include "vendor/ImGUI/imgui_impl_glfw.h"
#include "vendor/ImGUI/imgui_impl_opengl3.h"

#include "Core/Core.h"
#include "Core//Event.h"
#include "Core/Input.h"
#include "Core/Window.h"
#include "Core/KeyCode.h"
#include "Render/Renderer2D.h"
#include "Objects2D/Basic2D.h"
#include "ECS/Component.h"
#include "ECS/ComponentManager.h"

#include "Objects2D/Basic2D.h"
#include "Objects2D/Player.h"
#include "Core/AllStatics.h"
#include "Render/Renderer.h"

#include "Core/Collision.h"
#include "Components/Transform.h"
int main(void)
{
	{
		Window::Init(); //инициализация окна
		glfwMakeContextCurrent(Window::GetWindow());
		glfwSwapInterval(0); // Enable vsync
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui_ImplGlfw_InitForOpenGL(Window::GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		ImGui::StyleColorsDark();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		glm::mat4 camera = glm::ortho(-20.0f, 20.0f, -15.f, 15.f, -10.0f, 10.0f); //initialize the camera
		
		Player background("Background", 0, 0);
		background.collision->Enable = false;
		background.transform->Scale(40, 40);
		background.SetTexture("src/Images/background.jpg");
		background.SetShader(background.SHADER_TEXTURE);
		Collision Ground(0, -13.f);
		Ground.Enable = true;
		Ground.Static = true;
		Ground.Scale(50, 5);

		Player first("Player",10,10);
		first.transform->Scale(1.f, 1.f);
		first.SetTexture("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Images/car.png");

		Player Second("Player1", 0.0f, 2.0f);
		Second.transform->Scale(3, 3);
		Second.SetColor(COLORS::Orange);

		float* color1 = new float[4];
		float* scale = new float[2];
		float* position = new float[2];
		bool iscollided = false;
		bool isvisible = false;
		bool my_tool_active = true;
		position[0] = 0;
		position[1] = 0;
		scale[0] = 0;
		scale[1] = 0;
		while (!glfwWindowShouldClose(Window::GetWindow())) {
			//first.MOVE(0,-9.8f);
			//Second.MOVE(0, -9.8f);
			Renderer::Clear();	//clear display
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
			ImGui::ColorEdit4("Color", color1);
			if (ImGui::Button("Change color")) {
				first.color = vec4(color1[0], color1[1], color1[2], 1);
				first.SetShader(GameObject::SHADER_COLOR);
			}
			ImGui::InputFloat2("Scale", scale, 3, 0);
			if (ImGui::Button("Scale object")) {
				first.transform->Scale(scale[0], scale[1]);
			}
			ImGui::InputFloat2("Translate", position, 3, 0);
			if (ImGui::Button("Translate object")) {
				first.transform->Translate(position[0], position[1]);
			}
			ImGui::Checkbox("See collisions", &isvisible);
			Collision::IsVisible = isvisible;
			// Display contents in a scrolling region
			ImGui::Text("Position of %s\n x: (%.3lf)   y: (%.3lf)",first.name.c_str(), first.transform->position.x,first.transform->position.y);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
			if (Input::IsKeyPressed(Keycode::KEY_W)) {
				first.MOVE(0,30);					//move object
			}
			if(Input::IsKeyPressed(Keycode::KEY_S)){
				first.MOVE(0, -30);
			}
			if (Input::IsKeyPressed(Keycode::KEY_D)) {
				first.MOVE(5, 0);
			}
			if (Input::IsKeyPressed(Keycode::KEY_A)) {
				first.MOVE(-5, 0);
			}
			if (Input::IsKeyPressed(Keycode::KEY_R)) {
				first.transform->Rotate(-2, glm::vec3(0, 0, 1));  //rotate object with angle and axis
			}
			else if (Input::IsKeyPressed(Keycode::KEY_Q)) {
				first.transform->Rotate(2, glm::vec3(0, 0, 1));
			}
			if (Input::IsKeyPressed(Keycode::KEY_F)) {
				first.transform->position.x = 0;
				first.transform->position.y = 0;
			}
			if (Input::IsKeyPressed(Keycode::KEY_UP)) {
				Second.MOVE(0, 30);					//move object
			}
			if (Input::IsKeyPressed(Keycode::KEY_DOWN)) {
				Second.MOVE(0, -30);
			}
			if (Input::IsKeyPressed(Keycode::KEY_RIGHT)) {
				Second.MOVE(9, 0);
			}
			if (Input::IsKeyPressed(Keycode::KEY_LEFT)) {
				Second.MOVE(-9, 0);
			}
			if (Input::IsKeyPressed(Keycode::KEY_V)) {
				Second.transform->Rotate(-2, glm::vec3(0, 0, 1));  //rotate object with angle and axis
			}
			else if (Input::IsKeyPressed(Keycode::KEY_B)) {
				Second.transform->Rotate(2, glm::vec3(0, 0, 1));
			}
			if (Input::IsKeyPressed(Keycode::KEY_G)) {
				Second.transform->position.x = 0;
				Second.transform->position.y = 0;
			}
			DeltaTime::calculateDeltaTime();
			Renderer::Render(camera);//render all objects that we have in our scene
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			
			glfwSwapBuffers(Window::GetWindow());
			
			glfwPollEvents();

		}
	}
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}

