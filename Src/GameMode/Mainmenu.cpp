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

	//ModeMgr->ChangeMode(eModeTypes_Play);
}

void CMainmenu::Open()
{
	CBaseMode::Open();
	m_pSkyBg->SetShow(true);
}

void CMainmenu::Close()
{
	CBaseMode::Close();
	m_pSkyBg->SetShow(false);
}
