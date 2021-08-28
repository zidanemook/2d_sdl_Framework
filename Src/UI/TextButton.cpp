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

	m_pFontTexture = CSingleTexture::Create();
	m_pIdle_Image = NULL;
	m_pClicked_Image = NULL;
	m_pOnMouse_Image = NULL;
	m_pImageTexture = NULL;
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
	if (false == m_bShow)
		return;

	if (m_pImageTexture)
	{
		SDL_SetTextureBlendMode(m_pImageTexture->GetTexture()->GetTexture(), m_pImageTexture->GetBlendMode());
		SDL_SetTextureAlphaMod(m_pImageTexture->GetTexture()->GetTexture(), m_pImageTexture->GetAlpha());
		
		RdrMgr->RenderCopy(m_pImageTexture->GetTexture()->GetTexture(), &m_pImageTexture->GetSrcRect(), &m_destRect);
	}
		
	//Font
	RdrMgr->RenderCopy(m_pFontTexture->GetTexture()->GetTexture(), &m_FontSrcRect, &m_FontDestRect);
	
	CUIWnd::Render();
}


void CTextButton::SetPos(SDL_Point& Point)
{
	CSingleTexture* pTexture = dynamic_cast<CSingleTexture*>(m_pFontTexture);
	if (true == pTexture->GetTexture()->GetLoaded())
	{
		if (m_pParent)
		{
			m_FontDestRect.x = m_pParent->GetPos().x + m_relativePos.x + (m_destRect.w - m_FontDestRect.w) / 2;
			m_FontDestRect.y = m_pParent->GetPos().y + m_relativePos.y + (m_destRect.h - m_FontDestRect.h) / 2;
		}
		else
		{
			m_FontDestRect.x = (m_destRect.w - m_FontDestRect.w) / 2;
			m_FontDestRect.y = (m_destRect.y - m_FontDestRect.y) / 2;
		}
	}
		
	CUIWnd::SetPos(Point);
}

void CTextButton::OnMouseLeftButtonUp(SDL_Event& event)
{
	m_pImageTexture = dynamic_cast<CSingleTexture*>(m_pOnMouse_Image);

	CUIWnd::OnMouseLeftButtonUp(event);
}

void CTextButton::OnMouseLeftButtonDown(SDL_Event& event)
{
	m_pImageTexture = dynamic_cast<CSingleTexture*>(m_pClicked_Image);

	CUIWnd::OnMouseLeftButtonDown(event);
}

void CTextButton::OnMouseOver(SDL_Event& event)
{
	m_pImageTexture = dynamic_cast<CSingleTexture*>(m_pOnMouse_Image);

	CUIWnd::OnMouseOver(event);
}

void CTextButton::OnMouseOut(SDL_Event& event)
{
	m_pImageTexture = dynamic_cast<CSingleTexture*>(m_pIdle_Image);

	CUIWnd::OnMouseOut(event);
}

void CTextButton::SetText(const std::wstring& wstText)
{
	m_Text = wstText;

	CSingleTexture* pTexture = dynamic_cast<CSingleTexture*>(m_pFontTexture);

	if (RSFONT->TextToTexture(wstText.c_str(), m_iTextSize, m_Color, pTexture->GetTexture()->GetTexturePointer(), m_FontTextureSize))
	{
		pTexture->GetTexture()->SetLoaded(true);
		m_FontSrcRect.h = m_FontTextureSize.y;
		m_FontSrcRect.w = m_FontTextureSize.x;
		m_FontSrcRect.x = 0;
		m_FontSrcRect.y = 0;

		m_FontDestRect.h = m_FontTextureSize.y;
		m_FontDestRect.w = m_FontTextureSize.x;

		if (m_pParent)
		{
			m_FontDestRect.x = m_pParent->GetPos().x + m_relativePos.x + (m_destRect.w - m_FontDestRect.w) / 2;
			m_FontDestRect.y = m_pParent->GetPos().y + m_relativePos.y + (m_destRect.h - m_FontDestRect.h) / 2;
		}
		else
		{
			m_FontDestRect.x = (m_destRect.w - m_FontDestRect.w) / 2;
			m_FontDestRect.y = (m_destRect.y - m_FontDestRect.y) / 2;
		}
		

		pTexture->Set(m_FontSrcRect, m_FontDestRect, eRenderLayer::eRenderLayer_UI, pTexture->GetTexture());
	}
}

void CTextButton::SetTextAsItemInDropButton(const std::wstring& wstText, CUIWnd* pParent)
{
	m_Text = wstText;

	CSingleTexture* pTexture = dynamic_cast<CSingleTexture*>(m_pFontTexture);

	if (RSFONT->TextToTexture(wstText.c_str(), m_iTextSize, m_Color, pTexture->GetTexture()->GetTexturePointer(), m_FontTextureSize))
	{
		pTexture->GetTexture()->SetLoaded(true);
		m_FontSrcRect.h = m_FontTextureSize.y;
		m_FontSrcRect.w = m_FontTextureSize.x;
		m_FontSrcRect.x = 0;
		m_FontSrcRect.y = 0;

		m_FontDestRect.h = m_FontTextureSize.y;
		m_FontDestRect.w = m_FontTextureSize.x;

		m_FontDestRect.x = pParent->GetPos().x + m_relativePos.x + (m_destRect.w - m_FontDestRect.w) / 2;
		m_FontDestRect.y = pParent->GetPos().y + m_relativePos.y + (m_destRect.h - m_FontDestRect.h) / 2;
	}
}

void CTextButton::SetIdleImage(CComponent* pImage)
{
	if (!pImage)
		return; 

	m_pIdle_Image = pImage;

	m_pImageTexture = dynamic_cast<CSingleTexture*>(m_pIdle_Image);

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

void CTextButton::SetShow(bool bSet)
{
	if (false == m_pImageTexture->GetTexture()->GetLoaded())
	{
		RSCMgr->LoadTexture(m_pImageTexture->GetTexture()->GetName(), m_pImageTexture->GetTexture()->GetPath());
	}

	CUIWnd::SetShow(bSet);
}

std::wstring& CTextButton::GetText()
{
	return m_Text;
}

CComponent* CTextButton::GetIdleImage()
{
	return m_pIdle_Image;
}

CComponent* CTextButton::GetClickedImage()
{
	return m_pClicked_Image;
}

CComponent* CTextButton::GetOnMouseImage()
{
	return m_pOnMouse_Image;
}

int CTextButton::GetTextSize()
{
	return m_iTextSize;
}

eUITextAlignType CTextButton::GetVerticalAlign()
{
	return m_VerticalAlign;
}

eUITextAlignType CTextButton::GetHorizontalAlign()
{
	return m_HorizontalAlign;
}



