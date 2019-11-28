#include "stdafx.h"
#include "UIWnd.h"

CUIWnd::CUIWnd()
{
}

CUIWnd::~CUIWnd()
{
}

void CUIWnd::Render()
{
	if (m_listChildren.empty())
		return;

	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	for (iter; iter != m_listChildren.end(); ++iter)
	{
		(*iter)->Render();
	}
}

void CUIWnd::HandleEvent(SDL_Event& event)
{
}

void CUIWnd::SetParent(CUIWnd* pWnd)
{
	m_pParent = pWnd;
}

void CUIWnd::AddChildren(CUIWnd* pWnd)
{
	if (!pWnd)
		return;

	m_listChildren.push_back(pWnd);
}

void CUIWnd::SetName(const wchar_t* pwszName)
{
	m_strName = pwszName;
}

void CUIWnd::SetUIType(eUIType eType)
{
	m_eUIType = eType;
}

void CUIWnd::SetPos(SDL_Point& Point)
{
	m_Pos = Point;
}

CUIWnd* CUIWnd::GetParent()
{
	return m_pParent;
}

CUIWnd* CUIWnd::GetChildren(wchar_t* pwszName)
{
	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();

	for (iter; iter != m_listChildren.end(); ++iter)
	{
		if ((*iter)->GetName() == pwszName)
		{
			return (*iter);
		}
	}

	return NULL;
}

std::wstring CUIWnd::GetName()
{
	return m_strName;
}

eUIType CUIWnd::GetUIType()
{
	return m_eUIType;
}

SDL_Point& CUIWnd::GetPos()
{
	return m_Pos;
}
