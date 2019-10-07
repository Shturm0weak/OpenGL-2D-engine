#include "glew.h"
#include "glfw3.h"
#include <conio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Render/VertexArray.h"
#include "Render/Shader.h"
#include "Render/Renderer.h"
#include "Render/Texture.h"

#include "Core/Core.h"

#include "Core/DeltaTime.h"

#include "Objects2D/Point2D.h"
#include "Objects2D/Triangle2D.h"
#include "Objects2D/car.h"



int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1280, 720, "OpenGL project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;

	{	
		Renderer renderer;
		glm::mat4 proj = glm::ortho(-20.0f,20.0f, -10.f, 10.f, -10.0f, 10.0f);
		Point2D q(55.f, StPos(-10.0f, 0.0f), Angle(30), renderer);
		Triangle2D w(55.f, StPos(10.0f, 0.0f), Angle(150), renderer);
		Point2D e(10.f, StPos(-10.0f, 2.0f), Angle(0),renderer);
		Point2D r(10.f, StPos(0.0f, 0.0f), Angle(180),renderer);
		Point2D t(10.f, StPos(-10.0f, 0.0f), Angle(30), renderer);
		Point2D y(10.f, StPos(10.0f, 0.0f), Angle(180), renderer);
		Point2D u(10.f, StPos(-10.0f, -1.0f), Angle(30),renderer);
		Point2D i(10.f, StPos( 10.0f, 0.0f), Angle(150),renderer);
		Point2D o(10.f, StPos(-4.0f, -4.0f), Angle(10), renderer);
		Point2D p(10.f, StPos(4.0f, -4.0f), Angle(180), renderer);
		Point2D a(10.f, StPos(-10.0f, -3.0f), Angle(70), renderer);
		Point2D s(10.f, StPos(-5.0f, -3.0f), Angle(0), renderer);
		Point2D d(10.f, StPos(5.0f, -3.0f), Angle(180), renderer);
		Point2D f(10.f, StPos(0.0f, 0.0f), Angle(60), renderer);
		Point2D g(10.f, StPos(11.0f, 4.0f), Angle(-135), renderer);
		Point2D h(10.f, StPos(-12.0f, 2.0f), Angle(90), renderer);
		Point2D j(10.f, StPos(0.0f, 0.0f), Angle(180), renderer);
		Point2D k(10.f, StPos(-13.0f, 0.0f), Angle(75), renderer);
		Point2D l(10.f, StPos(9.0f, 0.0f), Angle(180), renderer);
		Point2D z(10.f, StPos(-8.0f, -1.0f), Angle(30), renderer);
		Point2D x(10.f, StPos(7.0f, 0.0f), Angle(150), renderer);
		Point2D c(10.f, StPos(-8.0f, -4.0f), Angle(0), renderer);
		Point2D v(10.f, StPos(4.0f, -4.0f), Angle(180), renderer);
		Point2D b(10.f, StPos(-10.0f, -3.0f), Angle(70), renderer);
		Point2D n(2.f, StPos(-5.0f, -3.0f), Angle(0), renderer);
		Point2D m(2.f, StPos(5.0f, -3.0f), Angle(180), renderer);
		DeltaTime delta;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();	

			renderer.Render(proj, delta.calculateDeltaTime());
			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}
	glfwTerminate();

	return 0;
}