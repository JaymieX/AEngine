#pragma once

#include <Core/AEpch.h>

template <typename... Args>
class ISubscriber
{
public:
	virtual ~ISubscriber() = default;
	virtual void Invoke(Args... args) = 0;
	virtual bool IsInstanceOf(void* signature) = 0;
};

template <typename T, typename... Args>
class Subscriber : public ISubscriber<Args...>
{
public:
	Subscriber(T* t, void(T::*func)(Args...)) : t(t), func(func) {}
	void Invoke(Args... args) final { (t->*func)(args...); }
	bool IsInstanceOf(void* signature) final { return signature == static_cast<void*>(t); }
private:
	T* t;
	void(T::*func)(Args...);
};

class IEvent
{
public:
	virtual void UnSubscribe(void* t) = 0;
};

template <typename... Args>
class Event : public IEvent
{
public:
	void Execute(Args... args)
	{
		for(auto& func : subscribers)
			func->Invoke(args...);
	}

	template <typename T>
	void Subscribe(T* t, void(T::*func)(Args... args))
	{
		auto subscriber = new Subscriber<T, Args...>(t, func);
		subscribers.push_back(std::unique_ptr<ISubscriber<Args...>>(subscriber));
	}

	void UnSubscribe(void* t) final
	{
		auto subscriberToRemove = std::remove_if(
			subscribers.begin(), subscribers.end(),
			[t](auto& s) { return s->IsInstanceOf(t); }
		);

		subscribers.erase(subscriberToRemove, subscribers.end());
	}

private:
	std::vector<std::unique_ptr<ISubscriber<Args...>>> subscribers;
};

template<typename Derived>
class EventListener
{
public:
	~EventListener()
	{
		for(auto& e : events) e->UnSubscribe(static_cast<void*>(this));
	}
	
	template<typename... Args>
	void Listen(Event<Args...>& e, void(Derived::*methodToListen)(Args... args))
	{
		e.Subscribe(static_cast<Derived*>(this), methodToListen);
		events.push_back(&e);
	}
	
private:
	std::vector<IEvent*> events;
};