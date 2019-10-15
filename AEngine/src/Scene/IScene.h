#pragma once

class IScene 
{
public:
	explicit IScene() = default;
	virtual ~IScene() = default;

	virtual bool Create() = 0;
	virtual void Destroy() = 0;
	virtual void Update(const float) = 0;
	virtual void Render() const = 0;
};