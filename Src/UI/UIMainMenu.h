#pragma once
#include "CMessageHandler.h"

class CUIWnd;
class CUIMainMenu : public CMessageHandler
{
public:
	CUIMainMenu();
	~CUIMainMenu();

public:
	virtual void SetShow(bool bSet);

private:
	CUIWnd* m_pRootWnd;
};

