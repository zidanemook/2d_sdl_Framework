#include "stdafx.h"
#include "Option.h"
#include "../Manager/UIManager.h"
#include "../UI/UIOption.h"


COption::COption()
{
}

COption::~COption()
{
}

COption* COption::Create()
{
	COption* pInstance = new COption;

	if (!pInstance)
	{
		wprintf(L"COption::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void COption::Free(void)
{
	UIMGR->GetUIOption()->SetShow(false);
}

void COption::Init()
{
}

void COption::Update()
{
}

void COption::Open()
{
	CBaseMode::Open();
	UIMGR->GetUIOption()->SetShow(true);
}

void COption::Close()
{
	CBaseMode::Close();
	
}

void COption::Closed()
{
	UIMGR->GetUIOption()->SetShow(false);

	CBaseMode::Closed();
}
