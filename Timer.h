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
	double getLastTimeCalled(); //last time when we called update()
	double getStartTime();
	void Update();
	double getDeltaTime();
};

