#pragma once

//#include <Core/AEpch.h>
//
//class IEvent
//{
//	virtual 
//}
//
//class EventDispatcher
//{
//	template<typename T>
//	using EventFunc = std::function<void(T&)>;
//public:
//	EventDispatcher(IEvent& e) : event(e) {}
//
//	template<typename T>
//	void Dispatch(EventFunc<T> function)
//	{
//		function(*static_cast<T*>(&event));
//	}
//
//private:
//	IEvent& event;
//	
//};