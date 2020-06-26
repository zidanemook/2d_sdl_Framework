#pragma once

//#include "Base.h"
#include "MessageHandler.h"
#include "Define.h"

class CUIWnd : public CMessageHandler
{
public:
	CUIWnd();
	~CUIWnd();

protected:
	CUIWnd*				m_pParent;
	std::list<CUIWnd*>	m_listChildren;

	std::wstring		m_strName;//지정하지 않았으면 자동으로 이름짓도록할것
	eUIType				m_eUIType;
	SDL_Rect			m_srcRect;
	SDL_Rect			m_destRect;
	eUIEventState		m_evtState;
	bool				m_bmovable;
	bool				m_bShow;

	CMessageHandler*	m_pMessageHander;

public:
	virtual void		Render();
	virtual void		HandleEvent(SDL_Event& event);
	virtual SDL_Rect&	GetDestRect();
	virtual void		SetPos(SDL_Point& Point);
	virtual void		ProcessEvent(SDL_Event& event);
	virtual void		SetShow(bool set);

public:
	virtual void OnMouseLeftButtonUp(SDL_Event& event) {};
	virtual void OnMouseLeftButtonDown(SDL_Event& event) {};
	//virtual void OnMouseRightButtonUp() {};
	//virtual void OnMouseRightButtonDown() {};
	virtual void OnMouseOver(SDL_Event& event) {};
	virtual void OnMouseOut(SDL_Event& event) {};

public:
	void			SetSize(SDL_Point& size);
	void			SetParent(CUIWnd* pWnd);
	void			AddChildren(CUIWnd* pWnd);
	void			SetName(const wchar_t* pwszName);
	void			SetUIType(eUIType eType);
	void			SetMessageHandler(CMessageHandler* pHandler);
	void			SetMovable(bool set);

	CUIWnd*			GetParent();
	CUIWnd*			GetChildren(wchar_t* pwszName);
	std::wstring&	GetName();
	eUIType			GetUIType();
	SDL_Point		GetPos();
	bool			GetMovable();
	bool			GetShow();
	
private:


};

