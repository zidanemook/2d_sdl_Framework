#include "stdafx.h"
#include "UIMessageBox.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"
#include "../Manager/ModeManager.h"
#include "UIWnd.h"

CUIMessageBox::CUIMessageBox()
	:m_pRootWnd(NULL), m_eFuntionType(eUIMessageBoxFuntionType_None)
{

}

CUIMessageBox::~CUIMessageBox()
{

}

CUIMessageBox* CUIMessageBox::Create()
{
	CUIMessageBox* pInstance = new CUIMessageBox;

	if (!pInstance)
	{
		wprintf(L"CUIMessageBox::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CUIMessageBox::Free()
{
}

void CUIMessageBox::OnMouseLeftButtonUp(SDL_Event& event)
{
	CUIWnd* pWnd = UIMGR->GetFocusWnd();

	if (pWnd)
	{
		if (eUIMessageBoxFuntionType_ReturnToMainMenu == m_eFuntionType)
		{
			if (pWnd->GetName() == _T("MessageBox_Button_A"))
			{
				SetShow(false);
				ModeMgr->ChangeMode(eModeTypes_MainMenu);
			}
			else if (pWnd->GetName() == _T("MessageBox_Button_B"))
			{
				SetShow(false);
			}
			else if (pWnd->GetName() == _T("MessageBox_Exit_Button"))
			{
				SetShow(false);
			}
		}
		
	}
}



void CUIMessageBox::SetShow(bool bSet)
{
	if (m_bShow == bSet)
		return;

	if (!m_pRootWnd)
	{
		m_pRootWnd = UIMGR->LoadUIFile(_T("MessageBox.json"));
		m_pRootWnd->SetMessageHandler(this);
		SDL_Rect rect = m_pRootWnd->GetDestRect();

	}

	m_bShow = bSet;
	m_pRootWnd->SetShow(bSet);

	if (false == bSet)
	{
		m_eFuntionType = eUIMessageBoxFuntionType_None;
	}
	

}

bool CUIMessageBox::GetShow()
{
	return m_bShow;
}

void CUIMessageBox::SetFunctionType(eUIMessageBoxFuntionType eType)
{
	m_eFuntionType = eType;
}

eUIMessageBoxFuntionType CUIMessageBox::GetFunctionType()
{
	return m_eFuntionType;
}

