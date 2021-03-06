/*!
 * \class classname
 *
 * \brief 
 Store Texture. Used for sprite, ui, particle...etc

This has only one in memory and is used by several components.

 * \author mook
 * \date 7�� 2018
 */

#pragma once

#include "Base.h"
#include "SDL_image.h"
#include "Define.h"


class CTexture : public CBase
{
private:
	explicit CTexture();
	~CTexture();

public:
	static CTexture* Create();
	inline virtual void Free(void);

public:
	void			SetTexture(SDL_Texture * pTex);
	SDL_Texture*	GetTexture();
	SDL_Texture**	GetTexturePointer();
	void			SetPath(const wchar_t* wszPath);
	const wchar_t*	GetPath();
	void			SetBlendMode(SDL_BlendMode BlendMode);
	void			SetAlpha(Uint8 alpha);
	void			SetLoaded(bool bSet);
	bool			GetLoaded();
	void			SetName(const wchar_t* wszName);
	const wchar_t*	GetName();

private:
	SDL_Texture*	m_pTexture;
	std::wstring	m_wsPath;
	bool			m_bLoaded;
	std::wstring	m_wstrname;
};

