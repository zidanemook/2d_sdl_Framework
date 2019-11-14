#include "stdafx.h"
#include "SingleTexture.h"
#include "Texture.h"
#include "../Manager/RenderManager.h"
#include "Obj.h"
#include "Texture.h"

CSingleTexture::CSingleTexture()
{
	m_RendereLayer = eRenderLayer_UI;
	m_pTexture = CTexture::Create();
	m_bShow = false;
	
	m_BlendMode = SDL_BLENDMODE_NONE;
	m_uiAlpha = 255;
}


CSingleTexture::~CSingleTexture()
{
}

CSingleTexture* CSingleTexture::Create()
{
	CSingleTexture*		pInstance = new CSingleTexture;

	if (!pInstance)
	{
		wprintf(L"CSingleTexture::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

CSingleTexture* CSingleTexture::Create(CTexture* pTexture)
{
	CSingleTexture*		pInstance = new CSingleTexture;

	if (!pInstance)
	{
		wprintf(L"CSingleTexture::Create Failed\n");

		Safe_Release(pInstance);
	}

	pInstance->SetTexture(pTexture);

	return pInstance;
}

void CSingleTexture::Free(void)
{
	m_pTexture->Release();
	m_bShow = false;
}

void CSingleTexture::Update()
{
	
	
}

void CSingleTexture::Init()
{
	CComponent::Init();
}

void CSingleTexture::SetLayer(eRenderLayer eLayer)
{
	m_RendereLayer = eLayer;
}

eRenderLayer CSingleTexture::GetLayer()
{
	return m_RendereLayer;
}

//void CSingleTexture::SetTexture(SDL_Texture* pTexture)
//{
//	m_pTexture->SetTexture(pTexture);
//}

void CSingleTexture::SetTexture(CTexture* pTexture)
{
	m_pTexture = pTexture;
	pTexture->AddRef();
}

bool CSingleTexture::GetShow()
{
	return m_bShow;
}

void CSingleTexture::SetShow(bool set)
{
	if (m_bShow == set)
		return;

	m_bShow = set;
	if (true == m_bShow)
	{
		if(m_pTexture)
		{
			if (m_pOwner)
				RdrMgr->AddRenderCommand(m_pOwner->GetName(), m_pTexture->GetTexture(), NULL, NULL, m_RendereLayer, m_pOwner->GetPos(),&m_bShow, &m_BlendMode, &m_uiAlpha);
			else
			{
				RdrMgr->AddRenderCommand(m_pTexture->GetPath(), m_pTexture->GetTexture(), NULL, NULL, m_RendereLayer, &m_vDestPos, &m_bShow, &m_BlendMode, &m_uiAlpha);
			}	
		}
	}	
}

void CSingleTexture::Set(SDL_Rect& srcRect, SDL_Rect& destRect, eRenderLayer eLayer, CTexture* pTexture)
{
	m_SrcRect = srcRect;
	m_DestRect = destRect;
	m_RendereLayer = eLayer;
	m_pTexture = pTexture;
	m_vDestPos = Vector2D(float(destRect.x), float(destRect.y));
}

void CSingleTexture::SetBlendMode(SDL_BlendMode BlendMode)
{
	m_BlendMode = BlendMode;
}

void CSingleTexture::SetAlpha(Uint8 uiAlpha)
{
	m_uiAlpha = uiAlpha;
}

