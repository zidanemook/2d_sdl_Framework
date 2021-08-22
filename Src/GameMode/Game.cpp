#include "stdafx.h"
#include "Game.h"
#include "Define.h"
#include "../Manager/ObjMgr.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/RenderManager.h"
#include "../Manager/ControlManager.h"
#include "../Manager/KeyManager.h"
#include "../Manager/UIManager.h"
#include "../UI/UIMessageBox.h"
#include "Unit.h"
#include "Texture.h"
#include "SingleTexture.h"

#include "Transform.h"
#include "Player.h"

CGame::CGame()
{
}


CGame::~CGame()
{
}

CGame* CGame::Create()
{
	CGame*		pInstance = new CGame;

	if (!pInstance)
	{
		wprintf(L"CProgram::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGame::Free(void)
{
	UIMGR->GetUIMessageBox()->SetShow(false);
	OBJMGR->GetSelf()->SetShow(false);
}

void CGame::Init()
{
	
}

void CGame::Update()
{
	if (KEYMGR->CheckKey(eKeyFunc_Esc, PUSHKEY))
	{
		UIMGR->GetUIMessageBox()->SetShow(true);
	}
}

void CGame::Open()
{
	CBaseMode::Open();
	OBJMGR->GetSelf()->SetShow(true);
}

void CGame::Close()
{
	CBaseMode::Close();
}

void CGame::Closed()
{
	CBaseMode::Closed();
}
