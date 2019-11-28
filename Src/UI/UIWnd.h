#pragma once

#include "Base.h"
#include "Define.h"

class CUIWnd : public CBase
{
public:
	CUIWnd();
	~CUIWnd();

protected:
	CUIWnd*			m_pParent;
	std::list<CUIWnd*> m_listChildren;

	std::wstring	m_strName;//지정하지 않았으면 자동으로 이름짓도록할것
	eUIType			m_eUIType;
	SDL_Point		m_Pos;

public:
	virtual void		Render();
	virtual void		HandleEvent(SDL_Event& event);
public:
	void			SetParent(CUIWnd* pWnd);
	void			AddChildren(CUIWnd* pWnd);
	void			SetName(const wchar_t* pwszName);
	void			SetUIType(eUIType eType);
	void			SetPos(SDL_Point& Point);

	CUIWnd*			GetParent();
	CUIWnd*			GetChildren(wchar_t* pwszName);
	std::wstring	GetName();
	eUIType			GetUIType();
	SDL_Point&		GetPos();
};

