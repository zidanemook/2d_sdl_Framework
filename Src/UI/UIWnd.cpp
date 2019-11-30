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
	if (SDL_MOUSEMOTION <= event.type && SDL_MOUSEWHEEL >= event.type)
	{
		SDL_Point point;
		point.x = event.motion.x;
		point.y = event.motion.y;

		std::list<CUIWnd*>::reverse_iterator riter = m_listChildren.rbegin();
		for (riter; riter != m_listChildren.rend(); ++riter)
		{
			//가장 나중 출력되는 UI Rect 부터 순서대로 충돌하고 있는지 판단

			if (PointToRectCollision(point, (*riter)->GetDestRect()))
			{
				(*riter)->HandleEvent(event);
				break;
			}
				
		}
	}
}

SDL_Rect& CUIWnd::GetDestRect()
{
	return m_destRect;
}

void CUIWnd::SetSize(SDL_Point& size)
{
	m_destRect.w = size.x;
	m_destRect.h = size.y;
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
	

	if (m_pParent)
	{
		m_destRect.x = Point.x + m_pParent->GetPos().x;
		m_destRect.y = Point.y + m_pParent->GetPos().y;
	}
	else
	{
		m_destRect.x = Point.x;
		m_destRect.y = Point.y;
	}

	SDL_Point point;
	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	for (iter; iter != m_listChildren.end(); ++iter)
	{
		point.x = (*iter)->GetDestRect().x;
		point.y = (*iter)->GetDestRect().y;
		(*iter)->SetPos(point);
	}
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

SDL_Point CUIWnd::GetPos()
{
	SDL_Point point;
	point.x = m_destRect.x;
	point.y = m_destRect.y;
	return point;
}
