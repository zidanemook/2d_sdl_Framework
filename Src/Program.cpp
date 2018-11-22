#include "stdafx.h"
#include "Program.h"
#include "Define.h"

#include "Manager/ModeManager.h"
#include "Manager/SystemManager.h"
#include "Manager/RenderManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/KeyManager.h"
#include "Manager/ControlManager.h"
#include "Manager/ObjMgr.h"
#include "Game.h"
#include "Logo.h"
#include "Mainmenu.h"

const int TargetFPS = 60;
const float fFramedelaySecond = ONESECOND / float(TargetFPS);
static int FrameCounter = 0;

static Uint64 NOW = SDL_GetPerformanceCounter();
static Uint64 LAST = SDL_GetPerformanceCounter();
static float fTime = 0.f;

float deltaTime = 0.f;

CProgram::CProgram()
{
}

CProgram::~CProgram()
{
}

CProgram* CProgram::Create()
{
	CProgram*		pInstance = new CProgram;

	if (!pInstance)
	{
		wprintf(L"CProgram::Create Failed\n");
		
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CProgram::Free(void)
{
	//opposite of create





	//manager
	OBJMGR->DestroyInstance();
	ModeMgr->DestroyInstance();
	CTRLMGR->DestroyInst();
	KEYMGR->DestroyInst();
	RSCMgr->DestroyInstance();
	RdrMgr->DestroyInstance();
	SysMgr->DestroyInstance();
}

void CProgram::Init()
{
	m_bIsRunning = true;
	//Window, Device
	if (false == SysMgr->Init("Framework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, false))
	{
		m_bIsRunning = false;
		return;
	}
	else
	{
		if (false == RdrMgr->Init(SysMgr->GetWindow()))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init RenderManager Failed", "Init RenderManager Failed", NULL);
			m_bIsRunning = false;
			return;
		}
	}


	if (false == RSCMgr->Init())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Loading Resource Failed", "Loading resource failed. Please check resource folder", NULL);
		m_bIsRunning = false;
		return;
	}

	KEYMGR->Init();
	CTRLMGR;
	ModeMgr;
	OBJMGR->Initialize();

	//Logo 싱글텍스쳐 하나 fadein fadeout
	CLogo* pLogo = CLogo::Create();
	pLogo->Init();
	ModeMgr->AddMode(eModeTypes_Logo, pLogo);
	ModeMgr->ChangeMode(eModeTypes_Logo);

	//MainMenu
	CMainmenu* pMainmenu = CMainmenu::Create();
	pMainmenu->Init();
	ModeMgr->AddMode(eModeTypes_MainMenu, pMainmenu);

	//Loading 캐릭터 애니메이션 아무거나 달리게 하기. 팁 띄우기

	//Game
	CGame* pGame = CGame::Create();
	pGame->Init();
	ModeMgr->AddMode(eModeTypes_Play, pGame);
}

void CProgram::HandleEvents()
{
	SDL_Event sdlEvent;
	SDL_PollEvent(&sdlEvent);

	switch (sdlEvent.type)
	{
	case SDL_QUIT:
	{
		m_bIsRunning = false;
	}
	break;

	default:
		break;
	}
}

void CProgram::Update()
{
	HandleEvents();
	KEYMGR->UpdateKeyBoardState();
	CTRLMGR->Update();
	ModeMgr->Update();
	OBJMGR->Update();
	RdrMgr->Render();
	
	NOW = SDL_GetPerformanceCounter();
	deltaTime = ((NOW - LAST) / (float)SDL_GetPerformanceFrequency());

	LAST = NOW;

	//if (deltaTime < fFramedelaySecond)
	//{
		//Uint32 fDelay = Uint32((fFramedelaySecond - deltaTime) * 1000);
		//SDL_Delay(fDelay);
	//}

	FrameCounter++;
	fTime += deltaTime;
	if (fTime > ONESECOND)
	{	
		wprintf(_T("FPS: %d\n"), FrameCounter);
		FrameCounter = 0;
		fTime = 0.f;
	}
}

bool CProgram::IsRunning()
{
	return m_bIsRunning;
}

