#include "stdafx.h"
#include "FadeSystem.h"
#include "SingleTexture.h"
#include "../Manager/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../Manager/RenderManager.h"
#include "../Manager/SystemManager.h"

CFadeSystem* CFadeSystem::m_pInst = nullptr;

CFadeSystem::CFadeSystem()
: m_fCurrentAlpha( 0.0f )
{
	m_pBlack = CSingleTexture::Create();
	m_pBlack->SetTexture(RSCMgr->GetTextureByName(_T("FadeInFadeOut")));
	m_pBlack->SetBlendMode(SDL_BLENDMODE_BLEND);
	//m_pBlack->SetLayer(eRenderLayer_Fade);
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
	m_pBlack->Release();
}

void CFadeSystem::Initialize()//여러번 호출될수 있다!!
{
	m_fCurrentTime = 0.0f;
	m_bPlay = false;
	m_eFadeType = eFadeStage_Max;

}

void CFadeSystem::OnRender()
{
	if( m_bPlay == false )
	{
		if(true == m_pBlack->GetShow())
			m_pBlack->SetShow(false);
		return;
	}
	else
	{
		if (false == m_pBlack->GetShow())
			m_pBlack->SetShow(true);
	}
		

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

	m_pBlack->SetAlpha(Uint8(m_fCurrentAlpha * 255));


	//CSingleTexture* pSingleTexture = dynamic_cast<CSingleTexture*>(m_pBlack);
	
}

void CFadeSystem::Render()
{
	if (!m_bPlay)
		return;

	CTexture* pTexture = m_pBlack->GetTexture();
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = SYSMGR->GetWindowWidth();
	srcRect.h = SYSMGR->GetWindowHeight();
	SDL_Rect destRect = srcRect;
	
	SDL_SetTextureBlendMode(m_pBlack->GetTexture()->GetTexture(), m_pBlack->GetBlendMode());
	SDL_SetTextureAlphaMod(m_pBlack->GetTexture()->GetTexture(), m_pBlack->GetAlpha());
	RdrMgr->RenderCopy(pTexture->GetTexture(), &srcRect, &destRect);
	RdrMgr->RenderPresent();
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