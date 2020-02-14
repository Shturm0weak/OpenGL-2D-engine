#ifndef  DELTATIME_H
#define DELTATIME_H


class DeltaTime 
{
private:
	static float time;
	static float lasttime;
public:
	static float deltatime;
public:
	inline static double calculateDeltaTime() {
		time = (float)glfwGetTime();
		deltatime = fabs(lasttime - time);
		lasttime = time;
		return deltatime;
	};

};

#endif // ! DELTATIME_H