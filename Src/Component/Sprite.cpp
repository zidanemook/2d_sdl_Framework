#include "stdafx.h"
#include "Sprite.h"
#include "Texture.h"
#include "Obj.h"
#include "../Manager/RenderManager.h"

CSprite::CSprite()
{
	m_pTexture = CTexture::Create();
	m_bShow = true;
	m_eAnimationState = eAnimationState_Idle;
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
	if (true == m_bShow)
	{
		m_fTime += deltaTime;
		
		m_iCurrentFrame = int(m_fTime / (ONESECOND / float(m_Animation[m_eAnimationState].m_iFramePerSecond)));
		if (m_iCurrentFrame >= m_Animation[m_eAnimationState].m_iFrameTotalCount)
			m_iCurrentFrame = min(m_iCurrentFrame - m_Animation[m_eAnimationState].m_iFrameTotalCount, m_Animation[m_eAnimationState].m_iFrameTotalCount -1);

		if (ONESECOND <= m_fTime)
			m_fTime = 0.f;

		m_SrcRect.x = m_Animation[m_eAnimationState].m_iOriginX + (m_Animation[m_eAnimationState].m_iHorizontalFramePixelSize * m_iCurrentFrame);
		m_SrcRect.y = m_Animation[m_eAnimationState].m_iOriginY;
	}
}

void CSprite::Init()
{
	CComponent::Init();
}

bool CSprite::GetShow()
{
	return m_bShow;
}

void CSprite::SetShow(bool set)
{
	m_bShow = set;
	if (true == m_bShow)
	{
		if (m_pTexture)
		{
			if (m_pOwner)
				RdrMgr->AddRenderCommand(m_pOwner->GetName(), m_pTexture->GetTexture(), &m_SrcRect, &m_DestRect, m_pOwner->GetRenderLayer(), &m_bShow);
			else
			{
				RdrMgr->AddRenderCommand(m_pTexture->GetPath(), m_pTexture->GetTexture(), &m_SrcRect, &m_DestRect, eRenderLayer_Object, &m_bShow);
			}
		}
	}
}

int CSprite::GetCurrentFrame()
{
	return m_iCurrentFrame;
}

const stAnimData& CSprite::GetAnimData(eAnimationState eAnimState)
{
	return m_Animation[eAnimState];
}

void CSprite::SetAnimData(eAnimationState eAnimState, int iOriginX, int iOriginY, int HorizontalFramePixelSize, int VerticalFramePixelSize,  int iFrameTotalCount, int iFramePerSecond)
{
	if (eAnimState >= eAnimationState_Idle && eAnimState < eAnimationState_Max)
	{
		m_Animation[eAnimState].m_iOriginX = iOriginX;
		m_Animation[eAnimState].m_iOriginY = iOriginY;
		m_Animation[eAnimState].m_iHorizontalFramePixelSize = HorizontalFramePixelSize;
		m_Animation[eAnimState].m_iVerticalFramePixelSize = VerticalFramePixelSize;
		m_Animation[eAnimState].m_iFrameTotalCount = iFrameTotalCount;
		m_Animation[eAnimState].m_iFramePerSecond = iFramePerSecond;

		m_SrcRect.w = HorizontalFramePixelSize;
		m_SrcRect.h = VerticalFramePixelSize;
		m_DestRect.w = HorizontalFramePixelSize;
		m_DestRect.h = VerticalFramePixelSize;

		m_DestRect.x = 0;//testcode
		m_DestRect.y = 0;//testcode
	}
}

void CSprite::SetTexture(CTexture* pTexture)
{
	m_pTexture = pTexture;
	m_pTexture->AddRef();
}

eAnimationState CSprite::ToAnimationState(TCHAR* tszAnimState)
{
	if (_tcscmp(tszAnimState, _T("eAnimationState_Idle")) == 0)
	{
		return eAnimationState_Idle;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Dead")) == 0)
	{
		return eAnimationState_Dead;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Invincible")) == 0)
	{
		return eAnimationState_Invincible;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Left")) == 0)
	{
		return eAnimationState_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Right")) == 0)
	{
		return eAnimationState_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Up")) == 0)
	{
		return eAnimationState_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Down")) == 0)
	{
		return eAnimationState_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack")) == 0)
	{
		return eAnimationState_Attack;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Defence")) == 0)
	{
		return eAnimationState_Defence;
	}
	return eAnimationState_Idle;
}

void CSprite::SetAnimationState(eAnimationState eAnimState)
{
	m_eAnimationState = eAnimState;
}
