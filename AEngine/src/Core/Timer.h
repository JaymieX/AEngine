#pragma once

#include <Core/AEpch.h>
#include "AEApplication.h"
#include "Logger.h"

class Timer 
{
public:
	typedef void(AEApplication::*TimerAction)()const;

	Timer(const double rate) : sleepTime(GetSleepTime(rate)), previousTime(glfwGetTime()),
							   tickTime(previousTime), currentTime(0),
							   actionToPerform(nullptr), instance(nullptr),
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
			LOG_TRACE(std::to_string(frames) + "fps | " + std::to_string(deltaTime * 1000) + "ms", __FILE__, __LINE__);
			tickTime += 1.0;
			frames = 0;
		}
	}

	[[nodiscard]] inline double GetDeltaTime() const { return deltaTime; }
	[[nodiscard]] inline double GetCurrentTime() const { return currentTime; }
	
	inline void SetTimerAction(TimerAction action, AEApplication* instance) 
	{ 
		actionToPerform = action; this->instance = instance; 
	}

protected:
	static inline double GetSleepTime(const double fps) { return 1.0 / fps; }

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