#include "AEpch.h"
#include "AEApplication.h"

int main() {

	auto application = new AEApplication();

	if (application->Initialize())
		application->Run();

	delete application, application = nullptr;

	return 0;
}