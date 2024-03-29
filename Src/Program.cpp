#include "stdafx.h"
#include "Program.h"

#include "Manager/ModeManager.h"
#include "Manager/SystemManager.h"
#include "Manager/RenderManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/KeyManager.h"
#include "Manager/ControlManager.h"
#include "Manager/ObjMgr.h"
#include "Manager/UIManager.h"
#include "Manager/CTerrainManager.h"
#include "FadeSystem.h"
#include "Game.h"
#include "Logo.h"
#include "Mainmenu.h"
#include "Option.h"

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
	TERMGR->DestroyInst();
	OBJMGR->DestroyInstance();
	ModeMgr->DestroyInstance();
	CTRLMGR->DestroyInst();
	KEYMGR->DestroyInst();
	RSCMgr->DestroyInstance();
	RdrMgr->DestroyInstance();
	SYSMGR->DestroyInstance();
}

void CProgram::Init()
{
	m_bIsRunning = true;
	//Window, Device
	if (false == SYSMGR->Init("Framework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false))
	{
		m_bIsRunning = false;
		return;
	}
	else
	{
		if (false == RdrMgr->Init(SYSMGR->GetWindow()))
		{
			log("RdrMgr->Init");
			m_bIsRunning = false;
			return;
		}
	}


	if (false == RSCMgr->Init())
	{
		log("RSCMgr->Init");
		m_bIsRunning = false;
		return;
	}

	KEYMGR->Init();
	CTRLMGR;
	ModeMgr;
	OBJMGR->Initialize();
	TERMGR->Init();


	//Add Mode
	{
		//Logo 싱글텍스쳐 하나 fadein fadeout
		CLogo* pLogo = CLogo::Create();
		pLogo->Init();
		ModeMgr->AddMode(eModeTypes_Logo, pLogo);
		ModeMgr->ChangeMode(eModeTypes_Logo);

		//Loading 캐릭터 애니메이션 아무거나 달리게 하기. 팁 띄우기


		//MainMenu
		CMainmenu* pMainmenu = CMainmenu::Create();
		pMainmenu->Init();
		ModeMgr->AddMode(eModeTypes_MainMenu, pMainmenu);

		//Option
		COption* pOption = COption::Create();
		pOption->Init();
		ModeMgr->AddMode(eModeTypes_Option, pOption);


		//Game
		CGame* pGame = CGame::Create();
		pGame->Init();
		ModeMgr->AddMode(eModeTypes_Play, pGame);
	}
	
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
		break;
	}

	default:
	{
		UIMGR->HandleEvent(sdlEvent);
	}
		break;
	}
}

void CProgram::Update()
{
	HandleEvents();
	KEYMGR->UpdateKeyBoardState();
	CTRLMGR->Update();
	UIMGR->Update();
	ModeMgr->Update();
	OBJMGR->Update();
	TERMGR->Update();

	RdrMgr->RenderClear();
	RdrMgr->Render();
	UIMGR->Render();
	FadeSystem->Render();
	RdrMgr->RenderPresent();
	
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

