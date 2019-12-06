#pragma once

#include <Core/AEpch.h>

class Component;
class Entity;
class EntityManager;

using ComponentTypeID = std::size_t;
using EntityGroup = std::size_t;

inline ComponentTypeID getNewComponentTypeID()
{
	static ComponentTypeID id = 0u;
	return id++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept
{
	static ComponentTypeID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 64;
constexpr std::size_t maxGroups = 32;

using ComponentBitset = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Component() : boundEntity(nullptr) { }
	virtual ~Component() = default;

	virtual void Start() {}
	virtual void Update(const float dt) {}
	virtual void Render() {}
	virtual void ResizeUpdate() {}

	Entity* boundEntity;
};

class Entity
{
public:
	Entity() = delete;
	explicit Entity(EntityManager& manager) : manager(manager) { }

	void Update(const float dt)
	{
		for (auto& c: components) c->Update(dt);
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

	bool hasGroup(EntityGroup group)
	{
		return groupBitset[group];
	}

	void addGroup(EntityGroup group);

	void removeGroup(EntityGroup group)
	{
		groupBitset[group] = false;
	}

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

	EntityManager& manager;

	GroupBitset groupBitset;
	ComponentArray componentArray = ComponentArray();
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

	void Update(const float dt)
	{
		for (auto& entity : entities) entity->Update(dt);
	}

	void Render()
	{
		for (auto& entity : entities) entity->Render();
	}

	void ResizeUpdate()
	{
		for (auto& entity : entities) entity->ResizeUpdate();
	}

	void AddToGroup(Entity* entity, EntityGroup group)
	{
		groupedEntities[group].emplace_back(entity);
	}

	std::vector<Entity*> & getGroup(EntityGroup group)
	{
		return groupedEntities[group];
	}

	void SeekAndDestroy()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), [i](Entity* entity)
					{
						return !entity->isActive() || entity->hasGroup(i);
					}), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& entity)
			{
				return !entity->isActive();
			}
		), std::end(entities));
	}

	Entity* CreateAndAddEntity()
	{
		std::unique_ptr<Entity> entityPtr = std::make_unique<Entity>(*this);
		entities.emplace_back(std::move(entityPtr));
		return entities.at(entities.size() - 1).get();
	}

	template <typename ...T, typename ...TArgs>
	Entity* CreateAndAddEntity(TArgs&& ...componentArgs)
	{
		std::unique_ptr<Entity> entityPtr = std::make_unique<Entity>(*this);
		entityPtr->AddComponent<T>(componentArgs);
		entities.emplace_back(std::move(entityPtr));
		return entities.at(entities.size() - 1).get();
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};

