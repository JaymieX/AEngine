#pragma once

class AEApplication
{
public:
	 AEApplication();
	~AEApplication();

	bool Initialize();
	void Run();

private:
	std::unique_ptr<class Window> windowPtr;
};