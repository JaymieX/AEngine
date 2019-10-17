#pragma once

#include "Scene/IScene.h"

class CubeScene : public IScene
{
public: 
	explicit CubeScene() = default;

	virtual bool Initialize() override;
	virtual void Update(const float dt) override;
	virtual void Render() const override;
};