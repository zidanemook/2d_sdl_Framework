#include "stdafx.h"
#include "Program.h"

CProgram* pProgram = nullptr;

int wmain(int argc, char *argv[])
{
	pProgram = pProgram->Create();
	pProgram->Init();


	while (pProgram->IsRunning())
	{
		pProgram->Update();
	}

	pProgram->Release();

	return 0;
}
