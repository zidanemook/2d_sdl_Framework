#include "stdafx.h"
#include "UIMainMenu.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"
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
		
		SDL_Rect rect = m_pRootWnd->GetDestRect();
		SDL_Point point;
		point.x = (SysMgr->GetWindowWidth() - rect.w)/2;
		point.y = (SysMgr->GetWindowHeight() - rect.h)/2;
		m_pRootWnd->SetPos(point);
	}

	m_bShow = bSet;

	if (m_bShow)
		UIMGR->AddToRenderList(m_pRootWnd);
	else
		UIMGR->DeleteFromRenderListByName(m_pRootWnd->GetName());
}
