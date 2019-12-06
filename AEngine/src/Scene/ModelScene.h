#pragma once

#include "Scene/IScene.h"
#include "Rendering/GameObject.h"

class SceneGraph;

class ModelScene final : public IScene
{
public: 
	virtual bool Initialize() override;
	virtual void Update(const float dt) override;
	virtual void Render() const override;
	virtual void ResizeUpdate() const override;
	virtual void Destroy() const override;

	void HandleMouseReleasedEvent(int);

private:
	Entity* cameraEntityPtr = nullptr;
	Entity* lightEntityPtr = nullptr;
};

