#pragma once
#include "ConsoleColor.h"

#include "../vendor/ImGUI/imgui.h"
#include "../vendor/ImGUI/imgui_impl_glfw.h"
#include "../vendor/ImGUI/imgui_impl_opengl3.h"
#include "../Render/OrthographicCamera.h"

class Window {
private:
	Window() {}
	static GLFWwindow* m_window;
	static OrthographicCamera m_camera;

public:
	static int Init() {
		if (!glfwInit())
			return -1;

		m_window = glfwCreateWindow(1920, 1080, "OpenGL project", NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_window);

		if (glewInit() != GLEW_OK) {
			std::cout << "error" << std::endl;
			return -1;
		}
		std::cout << green << "Window initialized!" << white << std::endl;

		glfwMakeContextCurrent(Window::GetWindow());
		glfwSwapInterval(1); // Enable vsync
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui_ImplGlfw_InitForOpenGL(Window::GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		ImGui::StyleColorsDark();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}
	inline static GLFWwindow* GetWindow() { return m_window; }
	inline static OrthographicCamera& GetCamera() { return m_camera; }
};



