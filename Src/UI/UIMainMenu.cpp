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
		wprintf(L"CUIMainMenu::Create Failed\n");

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
		else if (pWnd->GetName() == _T("MainMenu_BG_Option"))
		{
			ModeMgr->ChangeMode(eModeTypes_Option);
		}
	}

}

void CUIMainMenu::SetShow(bool bSet)
{
	if (m_bShow == bSet)
		return;

	if (!m_pRootWnd)
	{
		m_pRootWnd = UIMGR->LoadUIFile(_T("MainMenu.json"));
		m_pRootWnd->SetMessageHandler(this);
	}

	m_bShow = bSet;
	m_pRootWnd->SetShow(bSet);
}
