#pragma once

#include <Core/AEpch.h>

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
	static ComponentTypeID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 64;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Component() : boundEntity(nullptr) { }
	virtual ~Component() = default;

	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void ResizeUpdate() {}

	Entity* boundEntity;
};

class Entity
{
public:	
	Entity() = default;
	
	Entity(Entity&& entity) noexcept :
		components(std::move(entity.components)),
		componentArray(entity.componentArray),
		componentBitset(entity.componentBitset),
		active(entity.active) { }


	void Update()
	{
		for (auto& c : components) c->Update();
	}

	void Render()
	{
		for (auto& c : components) c->Render();
	}

	void ResizeUpdate()
	{
		for (auto& c : components) c->ResizeUpdate();
	}

	void Destroy() { active = false; }

	[[nodiscard]] bool isActive() const { return active; }

	template <typename T>
	[[nodiscard]] bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>];
	}

	template <typename T, typename ...TArgs>
	T* AddComponent(TArgs&& ... componentArgs)
	{
		std::unique_ptr<T> newComponentPtr = std::make_unique<T>(std::forward<TArgs>(componentArgs)...);
		newComponentPtr->boundEntity = this;

		components.emplace_back(std::move(newComponentPtr));

		auto c = components.at(components.size() - 1).get();

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->Start();
		return static_cast<T*>(c);
	}

	template<typename T> T* GetComponent() const
	{
		auto componentPtr(componentArray[getComponentTypeID<T>()]);
		return static_cast<T*>(componentPtr);
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

	void ResizeUpdate()
	{
		for (auto& entity : entities) entity->ResizeUpdate();
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

	Entity* CreateAndAddEntity()
	{
		std::unique_ptr<Entity> entityPtr = std::make_unique<Entity>();
		entities.emplace_back(std::move(entityPtr));
		return entities.at(entities.size() - 1).get();
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
};

