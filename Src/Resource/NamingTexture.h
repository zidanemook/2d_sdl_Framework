#pragma once

#include "Base.h"
#include "SDL_image.h"
#include "Define.h"

class CNamingTexture : public CBase
{
private:
	explicit CNamingTexture();
	~CNamingTexture();

public:
	static CNamingTexture* Create();
	inline virtual void Free(void);

public:
	void			SetTexture(SDL_Texture* pTex);
	SDL_Texture* GetTexture();
	void			SetPath(const TCHAR* tszPath);
	const TCHAR* GetPath();
	void			SetBlendMode(SDL_BlendMode BlendMode);
	void			SetAlpha(Uint8 alpha);

private:
	SDL_Texture*	m_pTexture;
	tstring			m_tsPath;
	tstring			m_tsName;

};

