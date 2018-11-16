#pragma once

#include "Base.h"
#include "Define.h"

enum eModeState
{
	eModeState_None,
	eModeState_Open,
	eModeState_Opened,
	eModeState_Close,
	eModeState_Closed,
	eModeState_Max
};

class CBaseMode : public CBase
{

public:
	CBaseMode();
	virtual	~CBaseMode() {}

	virtual void Open();
	virtual void Opened() {}
	virtual void Close();
	virtual void Closed() {}
	virtual void Update() {}
	virtual void DrawUI() {}

	eModeState GetModeState();

	void SetFadeOpenTime(float fOpenFadeTime);
	float GetFadeOpenTime();
	void SetFadeCloseTime(float fCloseFadeTime);
	float GetFadeCloseTime();

protected:
	eModeState m_eModeState;
	bool m_bReserveClose;

	float m_fFadeOpenTime;
	float m_fFadeCloseTime;

	friend class CModeManager;
};