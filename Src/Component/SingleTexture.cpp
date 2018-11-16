#include "stdafx.h"
#include "SingleTexture.h"
#include "Texture.h"
#include "../Manager/RenderManager.h"
#include "Obj.h"
#include "Texture.h"

CSingleTexture::CSingleTexture()
{
	m_pTexture = CTexture::Create();
	m_bShow = true;
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
	m_bShow = set;
	if (true == m_bShow)
	{
		if(m_pTexture)
		{
			if (m_pOwner)
				RdrMgr->AddRenderCommand(m_pOwner->GetName(), m_pTexture->GetTexture(), NULL, NULL, eRenderLayer_UI, &m_bShow);
			else
			{
				RdrMgr->AddRenderCommand(m_pTexture->GetPath(), m_pTexture->GetTexture(), NULL, NULL, eRenderLayer_UI, &m_bShow);
			}	
		}
	}	
}
