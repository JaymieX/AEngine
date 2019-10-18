#pragma once

#include "Scene/IScene.h"

class CubeScene : public IScene
{
public: 
	virtual bool Initialize() override;
	virtual void Update(const float dt) override;
	virtual void Render() const override;

private:
	Entity* cubeEntityPtr = nullptr;
	Entity* cameraEntityPtr = nullptr;
};