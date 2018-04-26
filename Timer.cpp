#include "stdafx.h"
#include "Timer.h"

//milliseconds 级别的计时器
Timer::Timer()
{
	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	freq = double(t.QuadPart)/1000.0;
	Reset();
}


Timer::~Timer()
{
}

void Timer::Reset()
{
	QueryPerformanceCounter(&startTime);
	lastTimeCalled = double(startTime.QuadPart)/freq;
}

double Timer::getCurrentTime()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return double(t.QuadPart) / freq;
}

double Timer::getLastTimeCalled()
{
	return lastTimeCalled;
}

double Timer::getStartTime()
{
	return double(startTime.QuadPart) / freq;
}

void Timer::Update()
{
	lastTimeCalled = currentUptadeTime;
	currentUptadeTime = getCurrentTime();
}

double Timer::getDeltaTime()
{
	return currentUptadeTime - lastTimeCalled;
}
