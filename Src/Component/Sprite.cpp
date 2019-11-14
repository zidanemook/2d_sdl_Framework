#include "stdafx.h"
#include "Sprite.h"
#include "Texture.h"
#include "Obj.h"
#include "../Manager/RenderManager.h"

CSprite::CSprite()
{
	m_pTexture = CTexture::Create();
	m_bShow = false;
	m_eAnimationState = eAnimationState_Idle_Down;
	
	ZeroMemory(m_fSecondPerFrame, sizeof(m_fSecondPerFrame));

	ZeroMemory(&m_SrcRect, sizeof(SDL_Rect));
	ZeroMemory(&m_DestRect, sizeof(SDL_Rect));

	m_BlendMode = SDL_BLENDMODE_NONE;
	m_uiAlpha = 255;

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
		
		m_iCurrentFrame = int(m_fTime / m_fSecondPerFrame[m_eAnimationState]);
		if (m_iCurrentFrame >= m_Animation[m_eAnimationState].m_iFrameTotalCount)
			m_iCurrentFrame = min(m_iCurrentFrame - m_Animation[m_eAnimationState].m_iFrameTotalCount, m_Animation[m_eAnimationState].m_iFrameTotalCount -1);

		if (ONESECOND <= m_fTime)
			m_fTime = 0.f;

		m_SrcRect.x = m_Animation[m_eAnimationState].m_iOriginX + (m_Animation[m_eAnimationState].m_iHorizontalFramePixelSize * m_iCurrentFrame);
		m_SrcRect.y = m_Animation[m_eAnimationState].m_iOriginY;

		if (m_pOwner)
		{
			m_DestRect.x = int(m_pOwner->GetPos()->m_x - (m_pOwner->GetDestWidth()/2));
			m_DestRect.y = int(m_pOwner->GetPos()->m_y - (m_pOwner->GetDestHeight()/2));
		}
		
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
				RdrMgr->AddRenderCommand(m_pOwner->GetName(), m_pTexture->GetTexture(), &m_SrcRect, &m_DestRect, m_pOwner->GetRenderLayer(), m_pOwner->GetPos(), &m_bShow, &m_BlendMode, &m_uiAlpha);
			else
			{
				RdrMgr->AddRenderCommand(m_pTexture->GetPath(), m_pTexture->GetTexture(), &m_SrcRect, &m_DestRect, eRenderLayer_Object, &m_vDestPos, &m_bShow, &m_BlendMode, &m_uiAlpha);
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
	if (eAnimState >= eAnimationState_Idle_Left && eAnimState < eAnimationState_Max)
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
	
		m_vDestPos = Vector2D(float(m_DestRect.x), float(m_DestRect.y));

		m_fSecondPerFrame[eAnimState] = ONESECOND / float(m_Animation[eAnimState].m_iFramePerSecond);
	}
}

void CSprite::SetTexture(CTexture* pTexture)
{
	m_pTexture = pTexture;
	m_pTexture->AddRef();
}

eAnimationState CSprite::ToAnimationState(TCHAR* tszAnimState)
{
	if (_tcscmp(tszAnimState, _T("eAnimationState_Idle_Left")) == 0)
	{
		return eAnimationState_Idle_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Idle_Right")) == 0)
	{
		return eAnimationState_Idle_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Idle_Up")) == 0)
	{
		return eAnimationState_Idle_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Idle_Down")) == 0)
	{
		return eAnimationState_Idle_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Walk_Left")) == 0)
	{
		return eAnimationState_Walk_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Walk_Right")) == 0)
	{
		return eAnimationState_Walk_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Walk_Up")) == 0)
	{
		return eAnimationState_Walk_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Walk_Down")) == 0)
	{
		return eAnimationState_Walk_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Left")) == 0)
	{
		return eAnimationState_Run_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Left_Up")) == 0)
	{
		return eAnimationState_Run_Left_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Up")) == 0)
	{
		return eAnimationState_Run_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Right_Up")) == 0)
	{
		return eAnimationState_Run_Right_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Right")) == 0)
	{
		return eAnimationState_Run_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Right_Down")) == 0)
	{
		return eAnimationState_Run_Right_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Down")) == 0)
	{
		return eAnimationState_Run_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Run_Left_Down")) == 0)
	{
		return eAnimationState_Run_Left_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Left")) == 0)
	{
		return eAnimationState_Attack_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Left_Up")) == 0)
	{
		return eAnimationState_Attack_Left_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Up")) == 0)
	{
		return eAnimationState_Attack_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Right_Up")) == 0)
	{
		return eAnimationState_Attack_Right_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Right")) == 0)
	{
		return eAnimationState_Attack_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Right_Down")) == 0)
	{
		return eAnimationState_Attack_Right_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Down")) == 0)
	{
		return eAnimationState_Attack_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Attack_Left_Down")) == 0)
	{
		return eAnimationState_Attack_Left_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Left")) == 0)
	{
		return eAnimationState_Talk_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Left_Up")) == 0)
	{
		return eAnimationState_Talk_Left_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Up")) == 0)
	{
		return eAnimationState_Talk_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Right_Up")) == 0)
	{
		return eAnimationState_Talk_Right_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Right")) == 0)
	{
		return eAnimationState_Talk_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Right_Down")) == 0)
	{
		return eAnimationState_Talk_Right_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Down")) == 0)
	{
		return eAnimationState_Talk_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Talk_Left_Down")) == 0)
	{
		return eAnimationState_Talk_Left_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Left")) == 0)
	{
		return eAnimationState_Beaten_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Left_Up")) == 0)
	{
		return eAnimationState_Beaten_Left_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Up")) == 0)
	{
		return eAnimationState_Beaten_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Right_Up")) == 0)
	{
		return eAnimationState_Beaten_Right_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Right")) == 0)
	{
		return eAnimationState_Beaten_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Right_Down")) == 0)
	{
		return eAnimationState_Beaten_Right_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Down")) == 0)
	{
		return eAnimationState_Beaten_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_Beaten_Left_Down")) == 0)
	{
		return eAnimationState_Beaten_Left_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Left")) == 0)
	{
		return eAnimationState_FallDown_Left;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Left_Up")) == 0)
	{
		return eAnimationState_FallDown_Left_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Up")) == 0)
	{
		return eAnimationState_FallDown_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Right_Up")) == 0)
	{
		return eAnimationState_FallDown_Right_Up;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Right")) == 0)
	{
		return eAnimationState_FallDown_Right;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Right_Down")) == 0)
	{
		return eAnimationState_FallDown_Right_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Down")) == 0)
	{
		return eAnimationState_FallDown_Down;
	}
	else if (_tcscmp(tszAnimState, _T("eAnimationState_FallDown_Left_Down")) == 0)
	{
		return eAnimationState_FallDown_Left_Down;
	}
	
 
	return eAnimationState_Idle_Down;
}

void CSprite::SetAnimationState(eAnimationState eAnimState)
{
	m_eAnimationState = eAnimState;
}

void CSprite::SetDestRectWidth(int iWidth)
{
	m_DestRect.w = iWidth;
}

void CSprite::SetDestRectHeight(int iHeight)
{
	m_DestRect.h = iHeight;
}
