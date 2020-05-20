#include "stdafx.h"
#include "Font.h"
#include "Function.h"
#include "../Manager/RenderManager.h"

CFont::CFont()
	//:m_pTexture(NULL)
{
}

CFont::~CFont()
{
}

CFont* CFont::Create()
{
	CFont* pInstance = new CFont;

	if (!pInstance)
	{
		wprintf(L"CFont::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CFont::Free()
{
}

//TTF_Font* CFont::OpenFont(wchar_t* path, int size)
//{
//	TTF_Font* pFont = TTF_OpenFont(WToM(path).c_str(), size);
//
//	if(!pFont)
//	{
//		wprintf(L"CFont::OpenFont Failed\n");
//		return NULL;
//	}
//
//	m_mapFont.insert(std::make_pair(size, pFont));
//
//	return pFont;
//}

TTF_Font* CFont::OpenFont(std::wstring wsPath, int size)
{
	TTF_Font* pFont = TTF_OpenFont(WToM(wsPath.c_str()).c_str(), size);

	if (!pFont)
	{
		wprintf(L"CFont::OpenFont Failed\n");
		return false;
	}

	m_mapFont.insert(std::make_pair(size, pFont));

	return pFont;
}

void CFont::TextToTexture(const wchar_t* text, int iSize, SDL_Color color, SDL_Texture** outTexture, SDL_Point& outPoint)
{
	if (NULL != (*outTexture))
	{
		SDL_DestroyTexture(*outTexture);
		*outTexture = NULL;
	}
	
	TTF_Font* pFont = NULL;

	std::map<int, TTF_Font*>::iterator iter = m_mapFont.find(iSize);
	if (iter == m_mapFont.end())
	{
		pFont = OpenFont(NORMALFONT, iSize);
	}
	else 
	{
		pFont = iter->second;
	}

	if (!pFont)
		return;

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(pFont, WToM(text).c_str(), color);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		(*outTexture) = SDL_CreateTextureFromSurface(SDLRdr, textSurface);
		if ((*outTexture) == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			outPoint.x = textSurface->w;
			outPoint.y = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}
