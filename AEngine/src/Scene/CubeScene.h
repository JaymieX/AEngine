#pragma once

#include "Scene/IScene.h"

class CubeScene : public IScene
{
public: 
	explicit CubeScene();
	virtual ~CubeScene();

	virtual bool Create() override;
	virtual void Update(const float dt) override;
	virtual void Render() const override;

private:
	std::unique_ptr<class GameObject> cubeObjPtr;
};