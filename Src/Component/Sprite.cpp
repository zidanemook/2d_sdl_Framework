#include "stdafx.h"
#include "Sprite.h"
#include "Texture.h"
#include "Obj.h"
#include "../Manager/RenderManager.h"

CSprite::CSprite()
{
	m_pTexture = CTexture::Create();
	m_bShow = true;
	Init();
}


CSprite::~CSprite()
{
}

CSprite* CSprite::Create()
{
	CSprite*		pInstance = new CSprite;

	if (!pInstance)
	{
		wprintf(L"CSprite::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSprite::Free(void)
{
	m_pTexture->Release();
}

void CSprite::Update()
{
	
}

void CSprite::Init()
{
	CComponent::Init();
	RdrMgr->AddRenderCommand(m_pOwner->GetName(), m_pTexture->GetTexture(), NULL, NULL, eRenderLayer_Object, &m_bShow);
}

bool CSprite::GetShow()
{
	return m_bShow;
}

void CSprite::SetShow(bool set)
{
	m_bShow = set;
}

int CSprite::GetCurrentFrame()
{
	return m_iCurrentFrame;
}

const stAnimData& CSprite::GetAnimData(eAnimationState eAnimState)
{
	return m_Animation[eAnimState];
}
