#include <Core/AEpch.h>
#include "Core/AEApplication.h"

int main() {

	if (AEApplication::GetInstance()->Initialize())
		AEApplication::GetInstance()->Run();

	return 0;
}