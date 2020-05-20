#pragma once

#include "Define.h"
#include "Base.h"
#include "SDL_ttf.h"
#include "SDL_image.h"


class CFont : public CBase
{
private:
	explicit CFont();
	~CFont();

public:
	static CFont* Create();
	inline virtual void Free();

public:
	//TTF_Font* OpenFont(wchar_t* path, int size);
	TTF_Font* OpenFont(std::wstring wsPath, int size);
	void TextToTexture(const wchar_t* text, int iSize, SDL_Color color, SDL_Texture** outTexture, SDL_Point& outPoint);

private:
	//SDL_Texture*	m_pTexture;
	//std::wstring	m_wsText;
	//SDL_Point		m_Size;
	//TTF_Font*		m_Font;

	std::map<int, TTF_Font*>	m_mapFont;
};

