#include "stdafx.h"
#include "Game.h"
#include "Define.h"
#include "../Manager/ObjMgr.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/RenderManager.h"
#include "../Manager/ControlManager.h"
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

}

void CGame::Init()
{
	CObj* pPlayer = CPlayer::Create();
	pPlayer->Init();

	OBJMGR->AddObj(pPlayer->GetName(), pPlayer);
}

void CGame::Update()
{
	//CTRLMGR->
	//OBJMGR->Update();
	//RdrMgr->Render();
}
