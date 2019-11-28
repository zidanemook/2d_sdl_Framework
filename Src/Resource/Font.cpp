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

bool CFont::OpenFont(wchar_t* path, int size)
{
	m_Font = TTF_OpenFont(WToM(path).c_str(), size);
	if(!m_Font)
	{
		wprintf(L"CFont::OpenFont Failed\n");
		return false;
	}
	
	return true;
}

bool CFont::OpenFont(std::wstring wsPath)
{
	return false;
}

void CFont::TextToTexture(const wchar_t* text, SDL_Color color, SDL_Texture** outTexture, SDL_Point& outPoint)
{
	if (NULL != (*outTexture))
	{
		SDL_DestroyTexture(*outTexture);
		*outTexture = NULL;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, WToM(text).c_str(), color);
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
