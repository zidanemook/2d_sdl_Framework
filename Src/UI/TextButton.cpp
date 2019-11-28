#include "stdafx.h"
#include "TextButton.h"
#include "Font.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/RenderManager.h"

CTextButton::CTextButton()
{
	m_Color.a = 255;
	m_Color.r = 255;
	m_Color.g = 255;
	m_Color.b = 255;
}

CTextButton::~CTextButton()
{
}

CTextButton* CTextButton::Create()
{
	CTextButton* pInstance = new CTextButton;

	if (!pInstance)
	{
		wprintf(L"CTextButton::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CTextButton::Free()
{
}

void CTextButton::Render()
{
	
	//Button Image



	//Font
	m_destRect.h = m_FontTextureSize.y;
	m_destRect.w = m_FontTextureSize.x;
	m_destRect.x = m_Pos.x;//부모위치를 더해야 한다!
	m_destRect.y = m_Pos.y;
	RdrMgr->RenderCopy(m_pTexture, &m_srcRect, &m_destRect);
	
	CUIWnd::Render();
}

void CTextButton::HandleEvent(SDL_Event& event)
{
}

void CTextButton::SetText(const wchar_t* pwszText)
{
	m_Text = pwszText;

	RSFONT->TextToTexture(pwszText, m_Color, &m_pTexture, m_FontTextureSize);

	m_srcRect.h = m_FontTextureSize.y;
	m_srcRect.w = m_FontTextureSize.x;
	m_srcRect.x = 0;
	m_srcRect.y = 0;
}

void CTextButton::SetText(const std::wstring& wstText)
{
	m_Text = wstText;

	RSFONT->TextToTexture(wstText.c_str(), m_Color, &m_pTexture, m_FontTextureSize);

	m_srcRect.h = m_FontTextureSize.y;
	m_srcRect.w = m_FontTextureSize.x;
	m_srcRect.x = 0;
	m_srcRect.y = 0;
}

void CTextButton::SetIdleImage(CComponent* pImage)
{
	m_pIdle_Image = pImage;
}

void CTextButton::SetClickedImage(CComponent* pImage)
{
	m_pClicked_Image = pImage;
}

void CTextButton::SetOnMouseImage(CComponent* pImage)
{
	m_pOnMouse_Image = pImage;
}

std::wstring& CTextButton::GetText()
{
	return m_Text;
}



