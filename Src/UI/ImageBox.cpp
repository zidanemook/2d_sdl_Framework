#include "stdafx.h"
#include "ImageBox.h"
#include "Component.h"
#include "SingleTexture.h"
#include "../Manager/RenderManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/UIManager.h"
#include "../Resource/Texture.h"

CImageBox::CImageBox()
	:m_pSingleTexture(NULL)
{
}

CImageBox::~CImageBox()
{
}

CImageBox* CImageBox::Create()
{
	CImageBox* pInstance = new CImageBox;

	if (!pInstance)
	{
		wprintf(L"CImageBox::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CImageBox::Free()
{
}

void CImageBox::Render()
{
	CSingleTexture* pSingleTexture = dynamic_cast<CSingleTexture*>(m_pSingleTexture);
	CTexture* pTexture = pSingleTexture->GetTexture();
	SDL_SetTextureBlendMode(pSingleTexture->GetTexture()->GetTexture(), pSingleTexture->GetBlendMode());
	SDL_SetTextureAlphaMod(pSingleTexture->GetTexture()->GetTexture(), pSingleTexture->GetAlpha());
	RdrMgr->RenderCopy(pTexture->GetTexture(), &m_srcRect, &m_destRect);

	CUIWnd::Render();
}

void CImageBox::SetShow(bool bSet)
{
	m_bShow = bSet;

	CSingleTexture* pSingleTexture = dynamic_cast<CSingleTexture*>(m_pSingleTexture);
	if (false == pSingleTexture->GetTexture()->GetLoaded())
	{
		RSCMgr->LoadTexture(pSingleTexture->GetTexture()->GetName(), pSingleTexture->GetTexture()->GetPath());

	}

	//CSingleTexture* pSingleTexture = dynamic_cast<CSingleTexture*>(m_pSingleTexture);

	//if (pSingleTexture && pSingleTexture->GetTexture())
	//{
	//	RdrMgr->AddRenderCommand(GetName(), pSingleTexture->GetTexture(), &m_srcRect, &m_destRect, eRenderLayer_UI, &m_bShow, &pSingleTexture->GetBlendMode(), &pSingleTexture->GetAlpha());
	//}

	CUIWnd::SetShow(bSet);
}

void CImageBox::OnMouseLeftButtonUp(SDL_Event& event)
{	
	if (m_bmovable && (this == UIMGR->GetFocusWnd()))
	{
		UIMGR->SetStickMouseWnd(NULL);
	}

	CUIWnd::OnMouseLeftButtonUp(event);
}

void CImageBox::OnMouseLeftButtonDown(SDL_Event& event)
{
	if (m_bmovable && (this == UIMGR->GetFocusWnd()))
	{
		UIMGR->SetStickMouseWnd(this);
	}
	
	CUIWnd::OnMouseLeftButtonDown(event);
}

void CImageBox::SetImage(CComponent* pTexture)
{
	if (!pTexture)
		return;

	m_pSingleTexture = pTexture;

	m_srcRect = dynamic_cast<CSingleTexture*>(m_pSingleTexture)->GetSrcRect();
}

CComponent* CImageBox::GetImage()
{
	return m_pSingleTexture;
}
