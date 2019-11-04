#include "../pch.h"
#include "WindowsInput.h"
#include "Window.h"

Input* Input::s_Instance = new WindowsInput();;

bool WindowsInput::IsKeyPressedimp(int keycode)
{
	const auto& window = static_cast<GLFWwindow*>(Window::GetWindow());

	auto state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS;
}
