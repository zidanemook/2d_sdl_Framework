#include "stdafx.h"
#include "TextButton.h"
#include "Font.h"
#include "SingleTexture.h"
#include "../Resource/Texture.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/RenderManager.h"

CTextButton::CTextButton()
{
	m_Color.a = 255;
	m_Color.r = 255;
	m_Color.g = 255;
	m_Color.b = 255;

	m_VerticalAlign = eUITextAlignType_Vertical_Center;
	m_HorizontalAlign = eUITextAlignType_Horizontal_Center;
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

	CSingleTexture* pIdle = dynamic_cast<CSingleTexture*>(m_pIdle_Image);
	RdrMgr->RenderCopy(pIdle->GetTexture()->GetTexture(), &m_srcRect, &m_destRect);


	//Font

	RdrMgr->RenderCopy(m_pTexture, &m_FontSrcRect, &m_FontDestRect);
	
	CUIWnd::Render();
}

void CTextButton::HandleEvent(SDL_Event& event)
{
}

void CTextButton::SetPos(SDL_Point& Point)
{
	if (m_pParent)
	{
		m_FontDestRect.x = m_pParent->GetPos().x + Point.x;
		m_FontDestRect.y = m_pParent->GetPos().y + Point.y;

		if(m_pIdle_Image)
		{
			if (m_HorizontalAlign == eUITextAlignType_Horizontal_Center)
			{
				SDL_Rect srcRect = dynamic_cast<CSingleTexture*>(m_pIdle_Image)->GetSrcRect();
				m_FontDestRect.x = m_pParent->GetPos().x + Point.x + (srcRect.w - m_FontDestRect.w) / 2;
			}

			if (m_VerticalAlign == eUITextAlignType_Vertical_Center)
			{
				SDL_Rect srcRect = dynamic_cast<CSingleTexture*>(m_pIdle_Image)->GetSrcRect();
				m_FontDestRect.y = m_pParent->GetPos().y + Point.y + (srcRect.h - m_FontDestRect.h) / 2;
			}
		}
		
	}
	else
	{
		m_FontDestRect.x = Point.x;
		m_FontDestRect.y = Point.y;

		if (m_pIdle_Image)
		{
			if (m_HorizontalAlign == eUITextAlignType_Horizontal_Center)
			{
				SDL_Rect srcRect = dynamic_cast<CSingleTexture*>(m_pIdle_Image)->GetSrcRect();
				m_FontDestRect.x = Point.x + (srcRect.w - m_FontDestRect.w) / 2;
			}

			if (m_VerticalAlign == eUITextAlignType_Vertical_Center)
			{
				SDL_Rect srcRect = dynamic_cast<CSingleTexture*>(m_pIdle_Image)->GetSrcRect();
				m_FontDestRect.y = Point.y + (srcRect.h - m_FontDestRect.h) / 2;
			}
		}
	}
		
	CUIWnd::SetPos(Point);
}

//void CTextButton::SetText(const wchar_t* pwszText)
//{
//	m_Text = pwszText;
//
//	RSFONT->TextToTexture(pwszText, m_iTextSize, m_Color, &m_pTexture, m_FontTextureSize);
//
//	m_FontSrcRect.h = m_FontTextureSize.y;
//	m_FontSrcRect.w = m_FontTextureSize.x;
//	m_FontSrcRect.x = 0;
//	m_FontSrcRect.y = 0;
//
//	m_FontDestRect.h = m_FontTextureSize.y;
//	m_FontDestRect.w = m_FontTextureSize.x;
//}

void CTextButton::SetText(const std::wstring& wstText)
{
	m_Text = wstText;

	RSFONT->TextToTexture(wstText.c_str(), m_iTextSize, m_Color, &m_pTexture, m_FontTextureSize);

	m_FontSrcRect.h = m_FontTextureSize.y;
	m_FontSrcRect.w = m_FontTextureSize.x;
	m_FontSrcRect.x = 0;
	m_FontSrcRect.y = 0;

	m_FontDestRect.h = m_FontTextureSize.y;
	m_FontDestRect.w = m_FontTextureSize.x;
}

void CTextButton::SetIdleImage(CComponent* pImage)
{
	if (!pImage)
		return; 

	m_pIdle_Image = pImage;

	m_srcRect = dynamic_cast<CSingleTexture*>(m_pIdle_Image)->GetSrcRect();
	SDL_Rect destRect = dynamic_cast<CSingleTexture*>(m_pIdle_Image)->GetDestRect();
	
	if (m_destRect.h == 0)
		m_destRect.h = destRect.h;
	if (m_destRect.w == 0)
		m_destRect.w = destRect.w;
}

void CTextButton::SetClickedImage(CComponent* pImage)
{
	m_pClicked_Image = pImage;
}

void CTextButton::SetOnMouseImage(CComponent* pImage)
{
	m_pOnMouse_Image = pImage;
}

void CTextButton::SetTextSize(int iSize)
{
	m_iTextSize = iSize;
}

void CTextButton::SetVerticalAlign(eUITextAlignType eType)
{
	m_VerticalAlign = eType;
}

void CTextButton::SetHorizontalAlign(eUITextAlignType eType)
{
	m_HorizontalAlign = eType;
}

std::wstring& CTextButton::GetText()
{
	return m_Text;
}



