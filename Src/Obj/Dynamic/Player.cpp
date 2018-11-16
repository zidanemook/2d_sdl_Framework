#include "stdafx.h"

#include "../../Manager/ResourceManager.h"
#include "Player.h"
#include "SingleTexture.h"


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

	//tstring tsName = _T("Player");
	//SetName(tsName);
	//SetRenderLayer(eRenderLayer_Object);
	//CComponent* pSingleTexture = dynamic_cast<CComponent*>(CSingleTexture::Create());
	//dynamic_cast<CSingleTexture*>(pSingleTexture)->SetTexture(RSCMgr->GetTextureByName(GetName()));
	//AddComponent(pSingleTexture);
}

void CPlayer::Update()
{
	CObj::Update();
}