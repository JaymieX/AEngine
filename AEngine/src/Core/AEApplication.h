#pragma once

class AEApplication
{
public:
	AEApplication(const AEApplication&) = delete;
	AEApplication(AEApplication&&) = delete;
	AEApplication& operator=(const AEApplication&) = delete;
	AEApplication& operator=(AEApplication&&) = delete;

	bool Initialize();
	void Run() const;

	static AEApplication* GetInstance();

	[[nodiscard]] glm::vec2 GetWindowSize() const;

private:
	AEApplication() = default;
   ~AEApplication();
	
	void BuildScene(class IScene*);
	void Update() const;
	void Render() const;
	
	bool sceneActive = false;

	std::unique_ptr<class IScene> scenePtr;
	std::unique_ptr<class Window> windowPtr;
	std::unique_ptr<class Timer> graphicsTimerPtr;

	static std::unique_ptr<AEApplication> instance;
	friend std::default_delete<AEApplication>;
};
