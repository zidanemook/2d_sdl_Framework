#include "stdafx.h"
#include "BaseMode.h"



CBaseMode::CBaseMode()
: m_eModeState( eModeState_None ), m_bReserveClose( false )
, m_fFadeOpenTime( 0.7f ), m_fFadeCloseTime( 0.7f )
{
}

void CBaseMode::Open()
{
	m_bReserveClose = false;
}

void CBaseMode::Close()
{
	m_bReserveClose = true;
}

eModeState CBaseMode::GetModeState()
{
	return m_eModeState;
}

void CBaseMode::SetFadeOpenTime(float fOpenFadeTime)
{
	m_fFadeOpenTime = fOpenFadeTime;
}

float CBaseMode::GetFadeOpenTime()
{
	return m_fFadeOpenTime;
}

void CBaseMode::SetFadeCloseTime(float fCloseFadeTime)
{
	m_fFadeCloseTime = fCloseFadeTime;
}

float CBaseMode::GetFadeCloseTime()
{
	return m_fFadeCloseTime;
}
