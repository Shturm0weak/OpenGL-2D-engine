#pragma once
#include "ConsoleColor.h"

class Window {
private:
	static GLFWwindow* m_window;
public:
	static int Init() {
		if (!glfwInit())
			return -1;

		m_window = glfwCreateWindow(1280, 720, "OpenGL project", NULL, NULL);
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
		return 0;
	}
	inline static GLFWwindow* GetWindow() { 
		
		return m_window; }
};



