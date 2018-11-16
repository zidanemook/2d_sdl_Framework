/*!
 * \class classname
 *
 * \brief 
 Store Texture. Used for sprite, ui, particle...etc

 * \author mook
 * \date 7¿ù 2018
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
	void			SetPath(const TCHAR* tszPath);
	const TCHAR*	GetPath();

private:
	SDL_Texture*	m_pTexture;
	tstring			m_tsPath;

};

