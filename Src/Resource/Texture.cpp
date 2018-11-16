#include "stdafx.h"
#include "Texture.h"
#include "../Manager/SystemManager.h"


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
}

CTexture* CTexture::Create()
{
	CTexture*		pInstance = new CTexture;

	if (!pInstance)
	{
		wprintf(L"CTexture::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTexture::Free(void)
{

}

void CTexture::SetTexture(SDL_Texture * pTex)
{
	m_pTexture = pTex;
}

SDL_Texture * CTexture::GetTexture()
{
	return m_pTexture;
}

void CTexture::SetPath(const TCHAR* tszPath)
{
	m_tsPath = tszPath;
}

const TCHAR* CTexture::GetPath()
{
	return m_tsPath.c_str();
}
