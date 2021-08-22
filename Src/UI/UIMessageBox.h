/*!
 * \class CUIMessageBox
 *
 *
 *
 * \brief
 *
 * TODO: long description
 *
 * \note
 *
 * \author mook
 *
 * \version 1.0
 *
 * \date 08¿ù 2021
 *
 *
 *
 */

#pragma once
#include "MessageHandler.h"

class CUIWnd;
class CUIMessageBox : public CMessageHandler
{
private:
	explicit CUIMessageBox();
	~CUIMessageBox();

public:
	static CUIMessageBox* Create();
	inline virtual void Free();

public:
	virtual void OnMouseOver(SDL_Event& event);
	virtual void OnMouseLeftButtonUp(SDL_Event& event);

public:
	virtual void SetShow(bool bSet);

private:
	CUIWnd* m_pRootWnd;

};

