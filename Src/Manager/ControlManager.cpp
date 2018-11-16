#include "stdafx.h"

#include "ControlManager.h"
#include "ObjMgr.h"
#include "KeyManager.h"

CControlManager*		CControlManager::m_pInst = NULL;

CControlManager::CControlManager(void)
{

}

CControlManager::~CControlManager(void)
{
}

void CControlManager::Update()
{
	if (KEYMGR->CheckKey(eKeyFunc_MoveLeft, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_MoveLeft, HOLDKEY))
	{
		wprintf(L"left\n");
	}
	if (KEYMGR->CheckKey(eKeyFunc_MoveRight, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_MoveRight, HOLDKEY))
	{
		wprintf(L"right\n");
	}
	if (KEYMGR->CheckKey(eKeyFunc_MoveUp, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_MoveUp, HOLDKEY))
	{
		wprintf(L"up\n");
	}
	if (KEYMGR->CheckKey(eKeyFunc_MoveDown, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_MoveDown, HOLDKEY))
	{
		wprintf(L"down\n");
	}
}

