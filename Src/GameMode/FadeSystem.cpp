#include "stdafx.h"
#include "FadeSystem.h"

CFadeSystem* CFadeSystem::m_pInst = nullptr;

CFadeSystem::CFadeSystem()
: m_fCurrentAlpha( 0.0f )
{
	Initialize();
}

CFadeSystem::~CFadeSystem()
{
	Destroy();
}

bool CFadeSystem::Create()
{
	return true;
}

void CFadeSystem::Destroy()
{

}

void CFadeSystem::Initialize()
{
	m_fCurrentTime = 0.0f;
	m_bPlay = false;
	m_eFadeType = eFadeStage_Max;
}

void CFadeSystem::OnRender()
{
	if( m_bPlay == false )
		return;

	m_fCurrentTime += deltaTime;

	double fLeftTime = m_fTotalTime - m_fCurrentTime;

	// 페이드 처리 종료
	if( m_fCurrentTime > m_fTotalTime )
	{
		fLeftTime = 0;
		m_bPlay = false;
	}

	// 점점 밝아짐 255 -> 0
	if( m_eFadeType == eFadeStage_In )
	{
		m_fCurrentAlpha = static_cast< float >( fLeftTime / m_fTotalTime );
	}
	// 점점 어두워짐 0 -> 255
	else if( m_eFadeType == eFadeStage_Out )
	{
		m_fCurrentAlpha = 1.0f - static_cast< float >( fLeftTime / m_fTotalTime );
	}
}

void CFadeSystem::StartFade( eFadeStage eFadeType, double fFadeTime )
{
	Initialize();
	if( 0 < fFadeTime )
		m_bPlay = true;
	else
		m_bPlay = false;

	m_eFadeType = eFadeType;
	if(eFadeStage_In == m_eFadeType )
		m_fCurrentAlpha = 1.0f;
	else if(eFadeStage_Out == m_eFadeType )
		m_fCurrentAlpha = 0.0f;

	m_fTotalTime = fFadeTime;
}