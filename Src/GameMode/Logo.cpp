#include "stdafx.h"
#include "Logo.h"
#include "Define.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/KeyManager.h"
#include "../Manager/ModeManager.h"
#include "../Component/SingleTexture.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

CLogo* CLogo::Create()
{
	CLogo*		pInstance = new CLogo;

	if (!pInstance)
	{
		wprintf(L"CLogo::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLogo::Free(void)
{
	m_pLogo->Release();
}

void CLogo::Init()
{
	m_pLogo = CSingleTexture::Create();
	m_pLogo->SetTexture(RSCMgr->GetTextureByName(_T("Logo")));
	
}

void CLogo::Update()
{
	if (KEYMGR->CheckKey(eKeyFunc_Enter, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Enter, HOLDKEY)
		|| KEYMGR->CheckKey(eKeyFunc_Interact, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Interact, HOLDKEY)
		|| KEYMGR->CheckKey(eKeyFunc_Esc, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_Esc, HOLDKEY) )
	{
		ModeMgr->ChangeMode(eModeTypes_MainMenu);
	}
}

void CLogo::Open()
{
	CBaseMode::Open();
	m_pLogo->SetShow(true);
}

void CLogo::Close()
{
	CBaseMode::Close();
	
}

void CLogo::Closed()
{
	CBaseMode::Closed();
	m_pLogo->SetShow(false);
}
