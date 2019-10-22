#pragma once
#include "glfw3.h"
#include <math.h>



class DeltaTime 
{
public:
	static double time;
	static double lasttime;
	static double deltatime;
public:
	inline static double calculateDeltaTime() {
		time = glfwGetTime();
		deltatime = fabs(lasttime - time);
		lasttime = time;
		return deltatime;
	};

};

  double DeltaTime::time;
  double DeltaTime::lasttime;
  double DeltaTime::deltatime;