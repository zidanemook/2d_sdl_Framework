#include "stdafx.h"
#include "TextBox.h"
#include "Font.h"
#include "SingleTexture.h"
#include "../Resource/Texture.h"
#include "../Manager/RenderManager.h"
#include "../Manager/ResourceManager.h"

CTextBox::CTextBox()
{
	m_Color.a = 255;
	m_Color.r = 255;
	m_Color.g = 255;
	m_Color.b = 255;

	m_VerticalAlign = eUITextAlignType_Vertical_Center;
	m_HorizontalAlign = eUITextAlignType_Horizontal_Center;

	m_pFontTexture = CSingleTexture::Create();
}

CTextBox::~CTextBox()
{
}

CTextBox* CTextBox::Create()
{
	CTextBox* pInstance = new CTextBox;

	if (!pInstance)
	{
		wprintf(L"CTextButton::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CTextBox::Free()
{
}

void CTextBox::Render()
{
	//Button Image

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

void CTextBox::SetPos(SDL_Point& Point)
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

void CTextBox::SetText(const std::wstring& wstText)
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

void CTextBox::SetImage(CComponent* pTexture)
{
	m_pImageTexture = dynamic_cast<CSingleTexture*>(pTexture);
}

CComponent* CTextBox::GetImage()
{
	return m_pImageTexture;
}

std::wstring& CTextBox::GetText()
{
	return m_Text;
}

void CTextBox::SetTextSize(int iSize)
{
	m_iTextSize = iSize;
}

void CTextBox::SetVerticalAlign(eUITextAlignType eType)
{
	m_VerticalAlign = eType;
}

void CTextBox::SetHorizontalAlign(eUITextAlignType eType)
{
	m_HorizontalAlign = eType;
}

void CTextBox::SetShow(bool bSet)
{

	if (false == m_pImageTexture->GetTexture()->GetLoaded())
	{
		RSCMgr->LoadTexture(m_pImageTexture->GetTexture()->GetName(), m_pImageTexture->GetTexture()->GetPath());
	}

	CUIWnd::SetShow(bSet);
}