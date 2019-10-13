#pragma once

class AEApplication
{
public:
	AEApplication();
	~AEApplication();

	AEApplication(AEApplication&) = delete;
	void operator=(AEApplication const&) = delete;

	bool Initialize();
	void Run();

private:
	void Update();
	void Render();

private:
	std::unique_ptr<class Window> windowPtr;
	std::unique_ptr<class EntityManager> entityManager;
};
