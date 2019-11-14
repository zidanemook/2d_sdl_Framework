#include "stdafx.h"
#include "Mainmenu.h"
#include "Define.h"
#include "../Manager/KeyManager.h"
#include "../Manager/ModeManager.h"
#include "../Manager/ResourceManager.h"
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
	m_pSkyBg->Release();
}

void CMainmenu::Init()
{
	m_pSkyBg = CSingleTexture::Create();
	m_pSkyBg->SetTexture(RSCMgr->GetTextureByName(_T("SkyBg")));
	
}

void CMainmenu::Update()
{
	if (KEYMGR->CheckKey(eKeyFunc_Enter, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Enter, HOLDKEY)
		|| KEYMGR->CheckKey(eKeyFunc_Interact, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Interact, HOLDKEY)
		|| KEYMGR->CheckKey(eKeyFunc_Esc, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Esc, HOLDKEY))
	{
		ModeMgr->ChangeMode(eModeTypes_Play);
	}
}

void CMainmenu::Open()
{
	CBaseMode::Open();
	m_pSkyBg->SetShow(true);
}

void CMainmenu::Close()
{
	CBaseMode::Close();
	
}

void CMainmenu::Closed()
{
	CBaseMode::Closed();
	m_pSkyBg->SetShow(false);
}
