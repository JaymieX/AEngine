#pragma once

#include <AEpch.h>

class Component;
class Entity;

using ComponentTypeID = std::size_t;

inline ComponentTypeID getComponentTypeID()
{
	static ComponentTypeID id = 0;
	return id++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 64;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	virtual ~Component() {}

	virtual void Start() {};
	virtual void Update() {};
	virtual void Render() {};

	Entity* owner;
};

class Entity
{
public:
	void Update()
	{
		for (auto& c : components) c->Update();
	}

	void Render()
	{
		for (auto& c : components) c->Render();
	}

	void Destroy() { active = false; }

	bool isActive() const { return active; }

	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentID<T>];
	}

	template <typename T, typename ...TArgs>
	T& addComponent(TArgs&& ... componentArgs)
	{
		T* c(new T(std::forward<TArgs>(componentArgs)...));
		c->entity = this;
		std::unique_ptr<Component> newComponentPtr{ c };
		components.emplace_back(std::move(newComponentPtr));

		componentArray[getComponentTypeID<T>()] = c;
		ComponentBitset[getComponentTypeID<T>()] = true;

		c->Start();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto componentPtr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(componentPtr);
	}

private:
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitset componentBitset;
	bool active = true;
};

class EntityManager
{
public:
	EntityManager() = default;

	~EntityManager() 
	{
	   for (auto& entity : entities) entity->Destroy();
	   SeekAndDestroy();
	}

	void Update()
	{
		for (auto& entity : entities) entity->Update();
	}

	void Render()
	{
		for (auto& entity : entities) entity->Render();
	}

	void SeekAndDestroy()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& entity)
			{
				return !entity->isActive();
			}
		), std::end(entities));
	}

	Entity& CreateAndAddEntity()
	{
		Entity* entity = new Entity();
		std::unique_ptr<Entity> entityPtr{ entity };
		entities.emplace_back(std::move(entityPtr));
		return *entity;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
};

