#pragma once
class Timer
{
private:
	double freq;
	LARGE_INTEGER startTime;
	double lastTimeCalled;
	double currentUptadeTime;
public:
	Timer();
	~Timer();
	void Reset(); //reset timer
	double getCurrentTime();
	double getLastTimeCalled(); //return the last time when we called Update()
	double getStartTime();
	void Update(); //update timer
	double getDeltaTime();
};

