#include "stdafx.h"
#include "UIMessageBox.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"
#include "UIWnd.h"

CUIMessageBox::CUIMessageBox()
	:m_pRootWnd(NULL)
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

void CUIMessageBox::OnMouseOver(SDL_Event& event)
{
}

void CUIMessageBox::OnMouseLeftButtonUp(SDL_Event& event)
{
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
		SDL_Point point;
		point.x = (SYSMGR->GetWindowWidth() - rect.w) / 2;
		point.y = (SYSMGR->GetWindowHeight() - rect.h) / 2;
		m_pRootWnd->SetPos(point);
	}

	m_bShow = bSet;
	m_pRootWnd->SetShow(bSet);
}

