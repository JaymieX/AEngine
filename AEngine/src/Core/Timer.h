#pragma once

#include <Core/AEpch.h>

class Timer 
{
	Timer() : currentTime(0.0), previousTime(0.0) {}
   ~Timer() {}

	Timer(Timer&) = delete;
	void operator=(Timer const&) = delete;

	void Update()
	{
		previousTime = currentTime;
		currentTime = glfwGetTime();
	}

	inline double GetDeltaTime() { return currentTime - previousTime; }
	inline double GetCurrentTime() { return currentTime; }
	inline bool CanPerformActionGivenRate(const double rate)
	{ 
		return GetSleepTime(rate) + previousTime > currentTime; 
	}

protected:
	inline double GetSleepTime(const double fps) { return 1000 / fps; }

protected:
	double currentTime;
	double previousTime;
};