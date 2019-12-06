#pragma once

#include "Systems/EntityComponent.h"

class IScene 
{
public:
	explicit IScene() = default;
	virtual ~IScene() = default;

	virtual bool Initialize() = 0;
	virtual void Update(const float) = 0;
	virtual void Render() const = 0;
	virtual void ResizeUpdate() const = 0;
	virtual void Destroy() const = 0;

protected:
	std::unique_ptr<EntityManager> sceneEntityManagerPtr;
	friend std::default_delete<IScene>;
};