#pragma once

class AEApplication
{
public:
	AEApplication();
	~AEApplication();

	AEApplication(AEApplication&) = delete;
	void operator=(AEApplication const&) = delete;

	bool Initialize();
	void Run() const;

private:
	void BuildScene(const unsigned int = 0);
	void Update() const;
	void AudioUpdate() const;
	void Render() const;

private:
	bool sceneActive = false;

	std::vector<class IScene*> scenes;

	std::unique_ptr<class IScene> scenePtr;
	std::unique_ptr<class Timer> graphicsTimerPtr;
	std::unique_ptr<class Timer> audioTimerPtr;
	std::unique_ptr<class Window> windowPtr;
	std::unique_ptr<class EntityManager> entityManager;
};
