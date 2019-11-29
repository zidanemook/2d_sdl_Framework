#pragma once

class CMessageHandler
{
public:
	CMessageHandler(): m_bShow(false){};
	~CMessageHandler() {};

public:
	virtual void SetShow(bool bSet) {};

public:
	virtual void OnMouseLeftButtonUp() {};
	virtual void OnMouseLeftButtonDown() {};
	virtual void OnMouseRightButtonUp() {};
	virtual void OnMouseRightButtonDown() {};

protected:
	bool	m_bShow;
};

