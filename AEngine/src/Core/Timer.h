#pragma once

#include <Core/AEpch.h>
#include "AEApplication.h"

class Timer 
{
public:
	typedef void(AEApplication::*TimerAction)();

	Timer(const double rate) : sleepTime(GetSleepTime(rate)), previousTime(glfwGetTime()),
							   tickTime(previousTime), currentTime(0),
							   actionToPerform(nullptr),
							   deltaTime(0), frames(0) 
							   { }
   ~Timer() {}

	Timer(Timer&) = delete;
	void operator=(Timer const&) = delete;

	void Update()
	{
		currentTime = glfwGetTime();
		if (currentTime - previousTime >= sleepTime)
		{
			frames++;
			deltaTime = currentTime - previousTime;
			previousTime = glfwGetTime();
			if (actionToPerform) (instance->*actionToPerform)();
		}

		if (currentTime - tickTime >= 1.0)
		{
			std::cout << frames << "fps | " << 1000.0 / double(frames) << "ms";
			std::cout << " Dt " << deltaTime * 1000 << "ms" << std::endl;
			tickTime += 1.0;
			frames = 0;
		}
	}

	inline double GetDeltaTime() { return deltaTime; }
	inline double GetCurrentTime() { return currentTime; }
	
	inline void SetTimerAction(TimerAction action, AEApplication* instance) 
	{ 
		actionToPerform = action; this->instance = instance; 
	}

protected:
	inline double GetSleepTime(const double fps) { return 1.0 / fps; }

protected:
	double currentTime;
	double previousTime;
	double deltaTime;
	double sleepTime;
	double tickTime;
	unsigned int frames;
	TimerAction actionToPerform;
	AEApplication* instance;
};