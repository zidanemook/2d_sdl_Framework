#include "stdafx.h"
#include "UIMainMenu.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"
#include "../Manager/ModeManager.h"
#include "UIWnd.h"

CUIMainMenu::CUIMainMenu()
	:m_pRootWnd(NULL)
{
	

}

CUIMainMenu::~CUIMainMenu()
{
}

CUIMainMenu* CUIMainMenu::Create()
{
	CUIMainMenu* pInstance = new CUIMainMenu;

	if (!pInstance)
	{
		wprintf(L"CTextButton::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CUIMainMenu::Free()
{
}

void CUIMainMenu::OnMouseOver(SDL_Event& event)
{

}

void CUIMainMenu::OnMouseLeftButtonUp(SDL_Event& event)
{
	CUIWnd* pWnd = UIMGR->GetFocusWnd();

	if (pWnd)
	{
		if( pWnd->GetName() == _T("MainMenu_BG_New") )
		{
			ModeMgr->ChangeMode(eModeTypes_Play);
		}
		else if (pWnd->GetName() == _T("MainMenu_BG_Exit"))
		{
			SDL_Event sdlevent;
			sdlevent.type = SDL_QUIT;
			SDL_PushEvent(&sdlevent);
		}
	}

}

void CUIMainMenu::SetShow(bool bSet)
{
	if (m_bShow == bSet)
		return;

	if (!m_pRootWnd)
	{
		m_pRootWnd = UIMGR->GetUIWndByName(_T("MainMenu"));
		m_pRootWnd->SetMessageHandler(this);
		SDL_Rect rect = m_pRootWnd->GetDestRect();
		SDL_Point point;
		point.x = (SysMgr->GetWindowWidth() - rect.w)/2;
		point.y = (SysMgr->GetWindowHeight() - rect.h)/2;
		m_pRootWnd->SetPos(point);
	}

	m_bShow = bSet;
	m_pRootWnd->SetShow(bSet);
}
