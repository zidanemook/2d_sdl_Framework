#include "stdafx.h"

#include "../../Manager/ResourceManager.h"
#include "Player.h"
#include "SingleTexture.h"
#include "Sprite.h"
#include "Transform.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

CPlayer* CPlayer::Create()
{
	CPlayer*		pInstance = new CPlayer;

	if (!pInstance)
	{
		wprintf(L"CPlayer::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer::Free()
{

}

void CPlayer::Init()
{
	CUnit::Init();

	tstring tsName = _T("Player");
	SetName(tsName);
	SetRenderLayer(eRenderLayer_Object);
	//CComponent* pSingleTexture = dynamic_cast<CComponent*>(CSingleTexture::Create());
	//dynamic_cast<CSingleTexture*>(pSingleTexture)->SetTexture(RSCMgr->GetTextureByName(GetName()));
	//AddComponent(pSingleTexture);
	
	m_iDestHeight = 72;
	m_iDestWidth = 52;

	AddComponent(RSCMgr->GetSpriteComponent(_T("Blond_RedArm_Man")));
	//dynamic_cast<CSprite*>(GetComponent(eComponentTypes_Sprite))->SetAnimationState(eAnimationState_Idle_Down);
	CComponent* pTransform = dynamic_cast<CTransform*>(CTransform::Create());
	AddComponent(pTransform);

	m_fMoveSpeed = 100.f;
}

void CPlayer::Update()
{
	CObj::Update();
}
