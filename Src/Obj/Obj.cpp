#include "stdafx.h"
#include "Obj.h"
#include "Component.h"
#include "Transform.h"
#include "../Component/Sprite.h"
#include "../Component/SingleTexture.h"



CObj::CObj()
{
	m_eRenderLayer = eRenderLayer_Object;
	m_bShow = true;
	m_eAnimState = eAnimationState_Idle_Down;
	m_fMoveSpeed = 1.f;
	m_eMoveDirection = eMoveDirection_Down;
	for (int i = eComponentTypes_None; i < eComponentTypes_Max; ++i)
	{
		m_Component[i] = NULL;
	}
}


CObj::~CObj()
{
}

void CObj::Free()
{
	//for_each(m_mapComponent.begin(), m_mapComponent.end(), ReleaseMapElement());
	//m_mapComponent.clear();
	for (int i = eComponentTypes_None; i < eComponentTypes_Max; ++i)
	{
		if (m_Component[i])
		{
			m_Component[i]->Release();
			m_Component[i] = NULL;
		}
	}

}

void CObj::Init()
{
	CComponent* pTransform = dynamic_cast<CComponent*>(CTransform::Create());
	AddComponent(pTransform);
}

void CObj::Update()
{
	//for_each(m_mapComponent.begin(), m_mapComponent.end(), UpdateMapElement());
	for (int i = eComponentTypes_None; i < eComponentTypes_Max; ++i)
	{
		if (m_Component[i])
		{
			m_Component[i]->Update();
		}
	}
}

void CObj::AddComponent(CComponent* pComponent)
{
	pComponent->SetOwner(this);

	if (m_Component[pComponent->GetComponentType()])
	{
		errormsg("AddComponent failed");
		return;
	}
	
	if (pComponent->GetComponentType() == eComponentTypes_Sprite)
	{
		dynamic_cast<CSprite*>(pComponent)->SetDestRectHeight(m_iDestHeight);
		dynamic_cast<CSprite*>(pComponent)->SetDestRectWidth(m_iDestWidth);
	}

	m_Component[pComponent->GetComponentType()] = pComponent;
}

CComponent* CObj::GetComponent(eComponentTypes eType)
{
	//std::map<tstring, CComponent*>::iterator Iter;
	//Iter = m_mapComponent.find(ComponentTypeToName(eType));
	//if (Iter != m_mapComponent.end())
	//	return Iter->second;
	if (m_Component[eType])
	{
		return m_Component[eType];
	}

	return NULL;
}

void CObj::SetName(std::wstring& pszName)
{
	static int UniqueObjID = 0;

	m_wsName = pszName;
	++UniqueObjID;

	if (0 > UniqueObjID)
		UniqueObjID = 0;

	m_wsName += UniqueObjID;
}

std::wstring& CObj::GetName()
{
	return m_wsName;
}

void CObj::SetRenderLayer(eRenderLayer eLayer)
{
	m_eRenderLayer = eLayer;
}

eRenderLayer CObj::GetRenderLayer()
{
	return m_eRenderLayer;
}

void CObj::SetPos(const Vector2D& vPos)
{
	if(GetComponent(eComponentTypes_Transform))
		dynamic_cast<CTransform*>(GetComponent(eComponentTypes_Transform))->SetPos(vPos);
}

void CObj::SetPos(const float x, const float y)
{
	if(GetComponent(eComponentTypes_Transform))
		dynamic_cast<CTransform*>(GetComponent(eComponentTypes_Transform))->SetPos(x, y);
}

Vector2D* CObj::GetPos()
{
	if(GetComponent(eComponentTypes_Transform))
		return dynamic_cast<CTransform*>(GetComponent(eComponentTypes_Transform))->GetPos();
	return NULL;
}

void CObj::SetShow(bool bSet)
{
	bool oldShow = m_bShow;
	m_bShow = bSet;


	if(GetComponent(eComponentTypes_Sprite))
		dynamic_cast<CSprite*>(GetComponent(eComponentTypes_Sprite))->SetShow(m_bShow);
	if(GetComponent(eComponentTypes_SingleTexture))
		dynamic_cast<CSingleTexture*>(GetComponent(eComponentTypes_SingleTexture))->SetShow(m_bShow);

	/*if ( (false == oldShow) && (true == m_bShow) )
	{
		if (GetComponent(eComponentTypes_Sprite))
			GetComponent(eComponentTypes_Sprite)->Init();
		if (GetComponent(eComponentTypes_SingleTexture))
			GetComponent(eComponentTypes_SingleTexture)->Init();
	}*/
}

bool CObj::GetShow()
{
	return m_bShow;
}

eAnimationState CObj::GetAnimState()
{
	return m_eAnimState;
}

void CObj::SetAnimState(eAnimationState eState)
{
	if(eAnimationState_Idle_Left <= eState && eAnimationState_Max > eState)
	{
		m_eAnimState = eState;
		dynamic_cast<CSprite*>(GetComponent(eComponentTypes_Sprite))->SetAnimationState(m_eAnimState);
	}
	

}

bool CObj::IsDying()
{
	if (eAnimationState_FallDown_Left <= m_eAnimState && eAnimationState_FallDown_Left_Down >= m_eAnimState)
	{
		return true;
	}
	return false;
}

bool CObj::IsDead()
{
	if (eAnimationState_FallDown_Left <= m_eAnimState && eAnimationState_FallDown_Left_Down >= m_eAnimState)
	{
		return IsAnimFinish(m_eAnimState);
	}
	return false;
}

bool CObj::IsAnimFinish(eAnimationState eState)
{
	CSprite* pSprite = dynamic_cast<CSprite*>(GetComponent(eComponentTypes_Sprite));
	if (pSprite)
	{
		if (pSprite->GetCurrentFrame() >= pSprite->GetAnimData(eState).m_iFrameTotalCount)
		{
			return true;
		}
		
	}
	return false;
}

void CObj::DoMove(eMoveDirection eDirection)
{
	if ( NULL == GetComponent(eComponentTypes_Transform))
		return;

	CTransform* pTransform = dynamic_cast<CTransform*>(GetComponent(eComponentTypes_Transform));
	if (NULL == pTransform)
		return;

	if (NULL == pTransform->GetPos())
		return;

	m_eMoveDirection = eDirection;

	

	switch (eDirection)
	{
	case eMoveDirection_Left:
	{
		pTransform->GetPos()->m_x -= m_fMoveSpeed * deltaTime;
		SetAnimState(eAnimationState_Walk_Left);
	}
		break;
	case eMoveDirection_Up:
	{
		pTransform->GetPos()->m_y -= m_fMoveSpeed * deltaTime;
		SetAnimState(eAnimationState_Walk_Up);
	}
		break;
	case eMoveDirection_Right:
	{
		pTransform->GetPos()->m_x += m_fMoveSpeed * deltaTime;
		SetAnimState(eAnimationState_Walk_Right);
	}
		break;
	case eMoveDirection_Down:
	{
		pTransform->GetPos()->m_y += m_fMoveSpeed * deltaTime;
		SetAnimState(eAnimationState_Walk_Down);
	}
		break;
	default:
		break;
	}
}

eMoveDirection CObj::GetMoveDirection()
{
	return m_eMoveDirection;
}

void CObj::SetDestWidth(int iWidth)
{
	m_iDestWidth = iWidth;
}

int CObj::GetDestWidth()
{
	return m_iDestWidth;
}

void CObj::SetDestHeight(int iHeight)
{
	m_iDestHeight = iHeight;
}

int CObj::GetDestHeight()
{
	return m_iDestHeight;
}
