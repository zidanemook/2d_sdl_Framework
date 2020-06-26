#include "stdafx.h"
#include "UIWnd.h"
#include "../Manager/UIManager.h"

CUIWnd::CUIWnd()
{
	m_pParent = NULL;
	m_pMessageHander = NULL;
	m_evtState = eUIEventState_None;
	m_bmovable = false;
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
	SDL_Point point;
	point.x = event.motion.x;
	point.y = event.motion.y;

	bool collision = false;
	std::list<CUIWnd*>::reverse_iterator riter = m_listChildren.rbegin();
	for (riter; riter != m_listChildren.rend(); ++riter)
	{
		if (PointToRectCollision(point, (*riter)->GetDestRect()))
		{
			(*riter)->HandleEvent(event);
			collision = true;
			break;
		}
	}

	if (true == m_listChildren.empty() || collision==false)
	{
		
		ProcessEvent(event);
		UIMGR->SetFocusWnd(this);
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

void CUIWnd::SetMessageHandler(CMessageHandler* pHandler)
{
	m_pMessageHander = pHandler;
}

void CUIWnd::SetMovable(bool set)
{
	m_bmovable = set;
}

void CUIWnd::SetShow(bool set)
{
	m_bShow = set;

	if (m_bShow)
		UIMGR->AddToRenderList(this);
	else
		UIMGR->DeleteFromRenderListByName(this->GetName());

	if (m_listChildren.empty())
	return;

	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	for (iter; iter != m_listChildren.end(); ++iter)
	{
		(*iter)->SetShow(set);
	}
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

void CUIWnd::ProcessEvent(SDL_Event& event)
{
	CUIWnd* pWnd = UIMGR->GetPreFocusWnd();
	if (pWnd)
	{
		if (pWnd != UIMGR->GetFocusWnd())
		{
			pWnd->OnMouseOut(event);
			UIMGR->SetPreFocusWnd(UIMGR->GetFocusWnd());
		}
	}

	if (event.type == SDL_MOUSEMOTION && event.button.button == 0)
	{
		OnMouseOver(event);
		if (m_pMessageHander)
			m_pMessageHander->OnMouseOver(event);
	}
	else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN)
	{
		OnMouseLeftButtonDown(event);
		if (m_pMessageHander)
			m_pMessageHander->OnMouseLeftButtonDown(event);
	}
	else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
	{
		OnMouseLeftButtonUp(event);
		if (m_pMessageHander)
			m_pMessageHander->OnMouseLeftButtonUp(event);
	}
	else if (event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONUP)
	{
		OnMouseRightButtonUp(event);
		if (m_pMessageHander)
			m_pMessageHander->OnMouseRightButtonUp(event);
	}

	if (m_pParent)
		m_pParent->ProcessEvent(event);
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

std::wstring& CUIWnd::GetName()
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

bool CUIWnd::GetMovable()
{
	return m_bmovable;
}

bool CUIWnd::GetShow()
{
	return m_bShow;
}
