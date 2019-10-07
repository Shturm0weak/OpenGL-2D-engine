#include "DeltaTime.h"
#include "glew.h"
#include "glfw3.h"
#include <math.h>

DeltaTime::DeltaTime()
{
	time = lasttime = deltatime = 0;
}

double DeltaTime::calculateDeltaTime()
{
	time = glfwGetTime();
	deltatime = fabs(lasttime - time);
	lasttime = time;
	return deltatime;
}
