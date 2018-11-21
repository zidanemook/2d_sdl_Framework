#include "stdafx.h"

#include "ControlManager.h"
#include "ObjMgr.h"
#include "KeyManager.h"
#include "Obj.h"

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
		OBJMGR->GetSelf()->DoMove(eMoveDirection_Left);
	}
	else if (KEYMGR->CheckKey(eKeyFunc_MoveLeft, PULLKEY))
	{
		OBJMGR->GetSelf()->SetAnimState(eAnimationState_Idle_Left);
	}

	if (KEYMGR->CheckKey(eKeyFunc_MoveRight, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_MoveRight, HOLDKEY))
	{
		OBJMGR->GetSelf()->DoMove(eMoveDirection_Right);
	}
	else if (KEYMGR->CheckKey(eKeyFunc_MoveRight, PULLKEY))
	{
		OBJMGR->GetSelf()->SetAnimState(eAnimationState_Idle_Right);
	}

	if (KEYMGR->CheckKey(eKeyFunc_MoveUp, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_MoveUp, HOLDKEY))
	{
		OBJMGR->GetSelf()->DoMove(eMoveDirection_Up);
	}
	else if (KEYMGR->CheckKey(eKeyFunc_MoveUp, PULLKEY))
	{
		OBJMGR->GetSelf()->SetAnimState(eAnimationState_Idle_Up);
	}

	if (KEYMGR->CheckKey(eKeyFunc_MoveDown, PUSHKEY) || KEYMGR->CheckKey(eKeyFunc_MoveDown, HOLDKEY))
	{
		OBJMGR->GetSelf()->DoMove(eMoveDirection_Down);
	}
	else if (KEYMGR->CheckKey(eKeyFunc_MoveDown, PULLKEY))
	{
		OBJMGR->GetSelf()->SetAnimState(eAnimationState_Idle_Down);
	}
}

