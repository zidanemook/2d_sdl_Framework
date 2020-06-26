#include "stdafx.h"
#include "Texture.h"
#include "../Manager/SystemManager.h"


CTexture::CTexture()
	: m_bLoaded(false), m_pTexture(NULL)
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

SDL_Texture** CTexture::GetTexturePointer()
{
	return &m_pTexture;
}

void CTexture::SetPath(const wchar_t* wszPath)
{
	m_wsPath = wszPath;
}

const wchar_t* CTexture::GetPath()
{
	return m_wsPath.c_str();
}

void CTexture::SetBlendMode(SDL_BlendMode BlendMode)
{
	SDL_SetTextureBlendMode(m_pTexture, BlendMode);
}

void CTexture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_pTexture, alpha);
}

void CTexture::SetLoaded(bool bSet)
{
	m_bLoaded = bSet;
}

bool CTexture::GetLoaded()
{
	return m_bLoaded;
}

void CTexture::SetName(const wchar_t* wszName)
{
	m_wstrname = wszName;
}

const wchar_t* CTexture::GetName()
{
	return m_wstrname.c_str();
}
