#include <Core/AEpch.h>
#include "Core/AEApplication.h"

int main() {

	if (AEApplication::GetInstance()->Initialize())
		AEApplication::GetInstance()->Run();

	_CrtDumpMemoryLeaks();
	exit(0);
}