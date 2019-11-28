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
	bool OpenFont(wchar_t* path, int size);
	bool OpenFont(std::wstring wsPath);
	void TextToTexture(const wchar_t* text, SDL_Color color, SDL_Texture** outTexture, SDL_Point& outPoint);

private:
	//SDL_Texture*	m_pTexture;
	//std::wstring	m_wsText;
	//SDL_Point		m_Size;
	TTF_Font*		m_Font;
};

