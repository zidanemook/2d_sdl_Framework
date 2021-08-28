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
	SDL_Rect			m_srcRect;//texture coordinate
	SDL_Rect			m_destRect;//screen coordinate
	SDL_Rect			m_relativePos;//parent coordinate
	eUIEventState		m_evtState;
	bool				m_bmovable;
	bool				m_bShow;
	bool				m_bRoot;

	CMessageHandler*	m_pMessageHander;

public:
	virtual void		Render();
	virtual void		HandleEvent(SDL_Event& event);
	virtual SDL_Rect&	GetDestRect();
	virtual void		SetRelativePos(SDL_Point& pos);
	virtual void		SetPos(SDL_Point& Point);
	virtual void		ProcessEvent(SDL_Event& event);
	virtual void		SetShow(bool set);

public:
	virtual void OnMouseLeftButtonUp(SDL_Event& event);
	virtual void OnMouseLeftButtonDown(SDL_Event& event);
	virtual void OnMouseRightButtonUp(SDL_Event& event);
	virtual void OnMouseRightButtonDown(SDL_Event& event);
	virtual void OnMouseOver(SDL_Event& event);
	virtual void OnMouseOut(SDL_Event& event);

public:
	void			SetSize(SDL_Point& size);
	void			SetSizeRate(SDL_Point& size);
	void			SetParent(CUIWnd* pWnd);
	void			AddChildren(CUIWnd* pWnd);
	void			DeleteChildren(std::wstring& strName);
	void			SetName(const wchar_t* pwszName);
	void			SetUIType(eUIType eType);
	void			SetMessageHandler(CMessageHandler* pHandler);
	void			SetMovable(bool set);
	void			SetRoot(bool set);

	CUIWnd*			GetRootWnd();
	CUIWnd*			GetParent();
	CUIWnd*			GetChildren(wchar_t* pwszName);
	std::wstring&	GetName();
	eUIType			GetUIType();
	SDL_Point		GetPos();
	bool			GetMovable();
	bool			GetShow();
	bool			GetRoot();
	
private:


};

