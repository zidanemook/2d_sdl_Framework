#include "stdafx.h"
#include "ImageBox.h"
#include "Component.h"
#include "SingleTexture.h"
#include "../Manager/RenderManager.h"
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
	SDL_Rect srcRect;
	srcRect = dynamic_cast<CSingleTexture*>(m_pSingleTexture)->GetSrcRect();
	
	SDL_Rect destRect;
	destRect = dynamic_cast<CSingleTexture*>(m_pSingleTexture)->GetDestRect();

	CTexture* pTexture = dynamic_cast<CSingleTexture*>(m_pSingleTexture)->GetTexture();
	RdrMgr->RenderCopy(pTexture->GetTexture(), &srcRect, &destRect);

	CUIWnd::Render();
}

void CImageBox::SetImage(CComponent* pTexture)
{
	m_pSingleTexture = pTexture;
}

CComponent* CImageBox::GetImage()
{
	return m_pSingleTexture;
}
