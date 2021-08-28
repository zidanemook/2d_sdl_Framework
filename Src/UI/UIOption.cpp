#include "stdafx.h"
#include "UIOption.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"
#include "../Manager/ModeManager.h"
#include "../Manager/RenderManager.h"
#include "DropButton.h"
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
		else if (pWnd->GetName() == _T("Option_BG_Resolution"))
		{
			CDropButton* pDropButton = dynamic_cast<CDropButton*>(pWnd);
			pDropButton->SetShowItems(true);			
		}
		else
		{
			CTextButton* pTextButton = dynamic_cast<CTextButton*>(pWnd);
			if (pTextButton)
			{
				if (pTextButton->GetText() == L"1920*1080")
				{
					SYSMGR->SetWindowWidth(FHD_WIDTH);
					SYSMGR->SetWindowHeight(FHD_HEIGHT);
				}
				else if (pTextButton->GetText() == L"1280*720")
				{
					SYSMGR->SetWindowWidth(HD_WIDTH);
					SYSMGR->SetWindowHeight(HD_HEIGHT);
				}

				SYSMGR->ChangeResolution();
				CDropButton* pDropButton = dynamic_cast<CDropButton*>(UIMGR->GetUIWndByName(_T("Option_BG_Resolution")));
				if (pDropButton)
					pDropButton->SetShowItems(false);
			}
		}
	
	}
	/*CDropButton* pDropButton = dynamic_cast<CDropButton*>(UIMGR->GetUIWndByName(L"Option_BG_Resolution"));	
	if (pDropButton)
	{
		pDropButton->SetShowItems(false);
	}*/
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

	if (false == bSet)
	{
		CDropButton* pDropButton = dynamic_cast<CDropButton*>(UIMGR->GetUIWndByName(_T("Option_BG_Resolution")));
		pDropButton->SetShowItems(false);
	}
	
	m_pRootWnd->SetShow(bSet);
}
