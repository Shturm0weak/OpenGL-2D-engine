#pragma once


class DeltaTime 
{
public:
	double time;
	double lasttime;
	double deltatime;

	DeltaTime();
	double calculateDeltaTime();
	double getTimeInMs() { return deltatime * 1000; }
	double getTimeInS() { return deltatime; }
};