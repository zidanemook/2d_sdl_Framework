#include "stdafx.h"
#include "UIMainMenu.h"
#include "../Manager/UIManager.h"
#include "UIWnd.h"

CUIMainMenu::CUIMainMenu()
	:m_pRootWnd(NULL)
{
	

}

CUIMainMenu::~CUIMainMenu()
{
}

void CUIMainMenu::SetShow(bool bSet)
{
	if (m_bShow == bSet)
		return;

	if (!m_pRootWnd)
	{
		m_pRootWnd = UIMGR->GetUIWndByName(_T("MainMenu_BG"));
	}

	m_bShow = bSet;

	if (m_bShow)
		UIMGR->AddToRenderList(m_pRootWnd);
	else
		UIMGR->DeleteFromRenderListByName(m_pRootWnd->GetName());
}
