#include "stdafx.h"
#include "Mainmenu.h"
#include "Define.h"
#include "../Manager/KeyManager.h"
#include "../Manager/ModeManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"
#include "../UI/UIMainMenu.h"
#include "../Component/SingleTexture.h"

CMainmenu::CMainmenu()
{
}


CMainmenu::~CMainmenu()
{
}

CMainmenu* CMainmenu::Create()
{
	CMainmenu*		pInstance = new CMainmenu;

	if (!pInstance)
	{
		wprintf(L"CMainmenu::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainmenu::Free(void)
{
	UIMGR->GetUIMainMenu()->SetShow(false);
	m_pSkyBg->Release();
}

void CMainmenu::Init()
{
	m_pSkyBg = CSingleTexture::Create();

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = SysMgr->GetWindowHeight();
	srcRect.w = SysMgr->GetWindowWidth();

	SDL_Rect destRect;
	destRect = srcRect;

	CTexture* pTexture = RSCMgr->GetTextureByName(_T("SkyBg"));

	m_pSkyBg->Set(srcRect, destRect, eRenderLayer_UI, pTexture);
	
	
}

void CMainmenu::Update()
{
	/*if (KEYMGR->CheckKey(eKeyFunc_Enter, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Enter, HOLDKEY)
		|| KEYMGR->CheckKey(eKeyFunc_Interact, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Interact, HOLDKEY))
	{
		ModeMgr->ChangeMode(eModeTypes_Play);
	}*/
}

void CMainmenu::Open()
{
	CBaseMode::Open();
	m_pSkyBg->SetShow(true);
	UIMGR->GetUIMainMenu()->SetShow(true);
}

void CMainmenu::Close()
{
	CBaseMode::Close();
	
}

void CMainmenu::Closed()
{
	UIMGR->GetUIMainMenu()->SetShow(false);
	m_pSkyBg->SetShow(false);
	CBaseMode::Closed();
}
