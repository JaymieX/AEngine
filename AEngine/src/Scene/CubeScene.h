#pragma once

#include "Scene/IScene.h"

class CubeScene final : public IScene
{
public: 
	virtual bool Initialize() override;
	virtual void Update(const float dt) override;
	virtual void Render() const override;
	virtual void ResizeUpdate() const override;

private:
	Entity* cubeEntityPtr = nullptr;
	Entity* cameraEntityPtr = nullptr;
};