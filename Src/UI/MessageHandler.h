#pragma once
#include "Base.h"

class CMessageHandler : public CBase
{
public:
	CMessageHandler(): m_bShow(false){};
	~CMessageHandler() {};

public:
	virtual void SetShow(bool bSet)=0;

public:
	virtual void OnMouseLeftButtonUp(SDL_Event& event) {};
	virtual void OnMouseLeftButtonDown(SDL_Event& event) {};
	virtual void OnMouseRightButtonUp(SDL_Event& event) {};
	virtual void OnMouseRightButtonDown(SDL_Event& event) {};
	virtual void OnMouseOver(SDL_Event& event) {};
	virtual void OnMouseOut(SDL_Event& event) {};

protected:
	bool	m_bShow;
};

