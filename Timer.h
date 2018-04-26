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
	void Reset();
	double getCurrentTime();
	double getLastTimeCalled();
	double getStartTime();
	void Update();
	double getDeltaTime();
};

