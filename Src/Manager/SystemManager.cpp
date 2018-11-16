#include "stdafx.h"
#include "SystemManager.h"

CSystemManager* CSystemManager::m_pInst = nullptr;

CSystemManager::CSystemManager()
{
}


CSystemManager::~CSystemManager()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

bool CSystemManager::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	bool bResult = false;
	int iFlag = 0;
	if (fullscreen)
	{
		iFlag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//wprintf(L"Sub system initialized\n");

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, iFlag);
		if (!m_pWindow)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Window failed", NULL);
		}
		else
			bResult = true;
	}
	else
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Sub system failed", NULL);
	}

	return bResult;
}

SDL_Window * CSystemManager::GetWindow()
{
	return m_pWindow;
}
