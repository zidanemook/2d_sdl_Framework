#include "stdafx.h"
#include "UIOption.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"
#include "../Manager/ModeManager.h"
#include "UIWnd.h"

CUIOption::CUIOption()
	:m_pRootWnd(NULL)
{
}

CUIOption::~CUIOption()
{
}

CUIOption* CUIOption::Create()
{
	CUIOption* pInstance = new CUIOption;

	if (!pInstance)
	{
		wprintf(L"CUIOption::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CUIOption::Free()
{
}

void CUIOption::OnMouseOver(SDL_Event& event)
{
}

void CUIOption::OnMouseLeftButtonUp(SDL_Event& event)
{
	CUIWnd* pWnd = UIMGR->GetFocusWnd();

	if (pWnd)
	{
		if (pWnd->GetName() == _T("Option_BG_Return"))
		{
			ModeMgr->ChangeMode(eModeTypes_MainMenu);
		}
	
	}
}

void CUIOption::SetShow(bool bSet)
{
	if (m_bShow == bSet)
		return;

	if (!m_pRootWnd)
	{
		m_pRootWnd = UIMGR->LoadUIFile(_T("Option.json"));
		m_pRootWnd->SetMessageHandler(this);
		SDL_Rect rect = m_pRootWnd->GetDestRect();
		SDL_Point point;
		point.x = (SYSMGR->GetWindowWidth() - rect.w) / 2;
		point.y = (SYSMGR->GetWindowHeight() - rect.h) / 2;
		m_pRootWnd->SetPos(point);
	}

	m_bShow = bSet;
	m_pRootWnd->SetShow(bSet);
}
