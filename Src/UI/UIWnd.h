#pragma once

#include "Base.h"
#include "Define.h"

class CMessageHandler;
class CUIWnd : public CBase
{
public:
	CUIWnd();
	~CUIWnd();

protected:
	CUIWnd*				m_pParent;
	std::list<CUIWnd*>	m_listChildren;

	std::wstring		m_strName;//�������� �ʾ����� �ڵ����� �̸��������Ұ�
	eUIType				m_eUIType;
	SDL_Rect			m_srcRect;
	SDL_Rect			m_destRect;

	CMessageHandler*	m_pMessageHander;

public:
	virtual void		Render();
	virtual void		HandleEvent(SDL_Event& event);
	virtual SDL_Rect&	GetDestRect();
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
	SDL_Point		GetPos();
	
};

