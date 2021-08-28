#include "stdafx.h"
#include "UIWnd.h"
#include "TextBox.h"
#include "TextButton.h"
#include "../Manager/UIManager.h"
#include "../Manager/SystemManager.h"

CUIWnd::CUIWnd()
{
	m_bShow = false;
	m_pParent = NULL;
	m_pMessageHander = NULL;
	m_evtState = eUIEventState_None;
	m_bmovable = false;
	m_bRoot = false;
}

CUIWnd::~CUIWnd()
{
}

void CUIWnd::Render()
{
	//if (m_listChildren.empty())
	//	return;

	//std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	//for (iter; iter != m_listChildren.end(); ++iter)
	//{
	//	if((*iter)->GetShow()==true)
	//	(*iter)->Render();
	//}
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
		if (PointToRectCollision(point, (*riter)->GetDestRect()) && (true == (*riter)->GetShow()))
		{
			(*riter)->HandleEvent(event);
			collision = true;
			break;
		}
	}

	if (collision==false)
	{
		ProcessEvent(event);
		UIMGR->SetFocusWnd(this);

		if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
		{
			//Move render order to top within this object's parent
			if (m_pParent && true == GetShow())
			{
				m_pParent->DeleteChildren(GetName());
				m_pParent->AddChildren(this);
			}

			//Move the render order of the root window of this object to the top
			CUIWnd* pRootWnd = GetRootWnd();
			if (pRootWnd && true == GetShow())
			{
				pRootWnd->SetShow(false);
				pRootWnd->SetShow(true);
			}
			
		}
		
	}
	
	

}

SDL_Rect& CUIWnd::GetDestRect()
{
	return m_destRect;
}

void CUIWnd::OnMouseLeftButtonUp(SDL_Event& event)
{
	if (m_pMessageHander)
		m_pMessageHander->OnMouseLeftButtonUp(event);

	if (m_pParent)
		m_pParent->OnMouseLeftButtonUp(event);
}

void CUIWnd::OnMouseRightButtonUp(SDL_Event& event)
{
	if (m_pMessageHander)
		m_pMessageHander->OnMouseRightButtonUp(event);

	if (m_pParent)
		m_pParent->OnMouseRightButtonUp(event);
}

void CUIWnd::OnMouseRightButtonDown(SDL_Event& event)
{
	if (m_pMessageHander)
		m_pMessageHander->OnMouseRightButtonDown(event);

	if (m_pParent)
		m_pParent->OnMouseRightButtonDown(event);
}

void CUIWnd::OnMouseLeftButtonDown(SDL_Event& event)
{
	if (m_pMessageHander)
		m_pMessageHander->OnMouseLeftButtonDown(event);

	if (m_pParent)
		m_pParent->OnMouseLeftButtonDown(event);
}

void CUIWnd::OnMouseOver(SDL_Event& event)
{
	if (m_pMessageHander)
		m_pMessageHander->OnMouseOver(event);

	if (m_pParent)
		m_pParent->OnMouseOver(event);
}

void CUIWnd::OnMouseOut(SDL_Event& event)
{
	if (m_pMessageHander)
		m_pMessageHander->OnMouseOut(event);

	if (m_pParent)
		m_pParent->OnMouseOut(event);
}

void CUIWnd::SetPos(SDL_Point& Point)
{
	if (m_pParent)
	{
		m_destRect.x = m_relativePos.x + m_pParent->GetPos().x;
		m_destRect.y = m_relativePos.y + m_pParent->GetPos().y;
	}
	else
	{
		m_destRect.x = Point.x;
		m_destRect.y = Point.y;
	}

	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	for (iter; iter != m_listChildren.end(); ++iter)
	{
		(*iter)->SetPos(Point);
	}
}

void CUIWnd::SetPosRate(SDL_Point& pos)
{
	m_PosRate = pos;
}

void CUIWnd::SetRePos()
{
	SDL_Point Pos;
	Pos.x = m_destRect.x;
	Pos.y = m_destRect.y;
	if (m_PosRate.x != 0 || m_PosRate.y != 0)
	{
		if(m_pParent)
			SetRelativePosRate(m_PosRate);
		else
		{
			float fscreenw = (float)SYSMGR->GetWindowWidth();
			float fscreenh = (float)SYSMGR->GetWindowHeight();
			Pos.x = int((float)m_PosRate.x * fscreenw / 100.f);
			Pos.y = int((float)m_PosRate.y * fscreenh / 100.f);
		}

		SetPos(Pos);
	}

	if (eUIType_TextBox == m_eUIType)
	{
		CTextBox* pTextBox = dynamic_cast<CTextBox*>(this);
		if (pTextBox)
		{
			pTextBox->SetText(pTextBox->GetText());
		}
	}
	else if (eUIType_TextButton == m_eUIType)
	{
		CTextButton* pTextButton = dynamic_cast<CTextButton*>(this);
		if (pTextButton)
		{
			pTextButton->SetText(pTextButton->GetText());
		}
	}

	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	for (iter; iter != m_listChildren.end(); ++iter)
	{
		(*iter)->SetRePos();
	}

}

void CUIWnd::SetSize(SDL_Point& size)
{
	m_destRect.w = size.x;
	m_destRect.h = size.y;
}

void CUIWnd::SetSizeRate(SDL_Point& size)
{
	m_SizeRate = size;

	float fscreenx = (float)SYSMGR->GetWindowWidth();
	float fscreeny = (float)SYSMGR->GetWindowHeight();
	m_destRect.w = int((float)size.x * fscreenx / 100.f);
	m_destRect.h = int((float)size.y * fscreeny / 100.f);
}

void CUIWnd::SetResize()
{
	if (m_SizeRate.x != 0 || m_SizeRate.y != 0)
		SetSizeRate(m_SizeRate);

	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	for (iter; iter != m_listChildren.end(); ++iter)
	{
		(*iter)->SetResize();
	}
}

void CUIWnd::SetRelativePos(SDL_Point& pos)
{
	//if (m_pParent)
	//{
		m_relativePos.x = pos.x;
		m_relativePos.y = pos.y;
	//}
}

void CUIWnd::SetRelativePosRate(SDL_Point& pos)
{
	m_PosRate = pos;

	//if (m_pParent)
	//{
		float fParentw = m_pParent->GetDestRect().w;
		float fParenth = m_pParent->GetDestRect().h;
		m_relativePos.x = int((float)pos.x * fParentw / 100.f);
		m_relativePos.y = int((float)pos.y * fParenth / 100.f);
	//}
	
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

void CUIWnd::DeleteChildren(std::wstring& wstrName)
{
	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();

	for (iter; iter != m_listChildren.end(); ++iter)
	{
		if ((*iter)->GetName() == wstrName)
		{
			m_listChildren.erase(iter);
			break;
		}
	}
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

void CUIWnd::SetRoot(bool set)
{
	m_bRoot = set;
}

void CUIWnd::SetShow(bool set)
{
	if (set == m_bShow)
		return;

	m_bShow = set;

	//if (m_bRoot)
	//{
		if (m_bShow)
			UIMGR->AddToRenderList(this);
		else
		{
			UIMGR->DeleteFromRenderListByName(this->GetName());
			UIMGR->SetStickMouseWnd(NULL);
		}
	//}
		
	if (m_listChildren.empty())
	return;

	std::list<CUIWnd*>::iterator iter = m_listChildren.begin();
	for (iter; iter != m_listChildren.end(); ++iter)
	{
		(*iter)->SetShow(set);
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
	}
	else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN)
	{
		OnMouseLeftButtonDown(event);
	}
	else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
	{
		OnMouseLeftButtonUp(event);	
	}
	else if (event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONUP)
	{
		OnMouseRightButtonUp(event);	
	}
}

CUIWnd* CUIWnd::GetRootWnd()
{
	CUIWnd* pRoot = m_pParent;
	if (!pRoot)
		return NULL;

	while (pRoot->GetParent())
	{
		pRoot = pRoot->GetParent();
	}
	return pRoot;
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

bool CUIWnd::GetRoot()
{
	return m_bRoot;
}

