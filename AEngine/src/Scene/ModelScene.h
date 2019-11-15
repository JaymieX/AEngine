#pragma once

#include "Scene/IScene.h"

class ModelScene : public IScene
{
public: 
	virtual bool Initialize() override;
	virtual void Update(const float dt) override;
	virtual void Render() const override;
	virtual void ResizeUpdate() const override;

private:
	Entity* modelEntityPtr = nullptr;
	Entity* cameraEntityPtr = nullptr;
	Entity* lightEntityPtr = nullptr;
};

