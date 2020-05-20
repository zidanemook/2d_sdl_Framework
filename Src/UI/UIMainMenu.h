#pragma once
#include "MessageHandler.h"

class CUIWnd;
class CUIMainMenu : public CMessageHandler
{
public:
	CUIMainMenu();
	~CUIMainMenu();

public:
	static CUIMainMenu* Create();
	inline virtual void Free();

public:
	virtual void OnMouseOver(SDL_Event& event);
	virtual void OnMouseLeftButtonUp(SDL_Event& event);

public:
	virtual void SetShow(bool bSet);

private:
	CUIWnd* m_pRootWnd;
};

