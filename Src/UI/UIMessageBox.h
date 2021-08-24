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


enum eUIMessageBoxFuntionType
{
	eUIMessageBoxFuntionType_None,
	eUIMessageBoxFuntionType_ReturnToMainMenu
};

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
	virtual void OnMouseLeftButtonUp(SDL_Event& event);


public:
	virtual void SetShow(bool bSet);
	bool		GetShow();

public:
	void SetFunctionType(eUIMessageBoxFuntionType eType);
	eUIMessageBoxFuntionType GetFunctionType();

private:
	CUIWnd* m_pRootWnd;
	eUIMessageBoxFuntionType m_eFuntionType;
};

