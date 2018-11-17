#include "stdafx.h"
#include "Define.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Component.h"
#include <atlstr.h>
#include <fstream> 

CResourceManager*		CResourceManager::m_pInst = nullptr;

CResourceManager::CResourceManager()
{
}


CResourceManager::~CResourceManager()
{
}

bool CResourceManager::Init()
{
	//TCHAR buffer[MAX_PATH];
	//GetModuleFileName(NULL, buffer, MAX_PATH);

	//tstring ExePath = buffer;
	
	if (false == LoadSingleTextureCSVFile(_T("Resource/Data/SingleTexture.csv")))
		return false;

	if (false == LoadSpriteTextureCSVFile(_T("Resource/Data/SpriteTexture.csv")))
		return false;

	return true;
}

void CResourceManager::Destroy()
{
	for_each(m_mapTexture.begin(), m_mapTexture.end(), ReleaseMapElement());
	m_mapTexture.clear();
}

bool CResourceManager::LoadSingleTextureCSVFile(const TCHAR* file)
{
	std::wifstream wif(file);

	if (wif.is_open())
	{
		wif.imbue(std::locale("kor"));

		TCHAR tszBuf[1024] = { 0, };

		wif.getline((WCHAR*)tszBuf, _countof(tszBuf));

		while (!wif.eof())
		{
			wif.getline((WCHAR*)tszBuf, _countof(tszBuf));

			TCHAR seps[] = TEXT(",");
			TCHAR *token;
			TCHAR pStr[MAX_PATH];
			TCHAR *next_token = NULL;
			//wcscpy_s(pStr, tszBuf);
			_tcscpy_s(pStr, tszBuf);
			//token = wcstok_s(pStr, seps, &next_token);
			token = _tcstok_s(pStr, seps, &next_token);
			if (!token) return false;
			TCHAR tszIndex[MAX_PATH] = { 0, };
			_tcscpy_s(tszIndex, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			TCHAR tszName[MAX_PATH] = { 0, };
			_tcscpy_s(tszName, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			TCHAR tszPath[MAX_PATH] = { 0, };
			_tcscpy_s(tszPath, token);

			LoadTexture(tszName, tszPath);
		}
	}
	else
		return false;

	return true;
}

bool CResourceManager::LoadSpriteTextureCSVFile(const TCHAR* file)
{
	std::wifstream wif(file);

	if (wif.is_open())
	{
		wif.imbue(std::locale("kor"));

		TCHAR tszBuf[1024] = { 0, };

		wif.getline((WCHAR*)tszBuf, _countof(tszBuf));

		while (!wif.eof())
		{
			wif.getline((WCHAR*)tszBuf, _countof(tszBuf));

			TCHAR seps[] = TEXT(",");
			TCHAR *token;
			TCHAR pStr[MAX_PATH];
			TCHAR *next_token = NULL;

			_tcscpy_s(pStr, tszBuf);
			token = _tcstok_s(pStr, seps, &next_token);
			if (!token) return false;
			TCHAR tszIndex[MAX_PATH] = { 0, };
			_tcscpy_s(tszIndex, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			TCHAR tszAnimationState[MAX_PATH] = { 0, };			
			_tcscpy_s(tszAnimationState, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			TCHAR tszName[MAX_PATH] = { 0, };
			_tcscpy_s(tszName, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			TCHAR tszPath[MAX_PATH] = { 0, };
			_tcscpy_s(tszPath, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			int OriginX = _ttoi(token);
			
			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			int OriginY = _ttoi(token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			int PixelSizeX = _ttoi(token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			int PixelSizeY = _ttoi(token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			int FrameTotalCount = _ttoi(token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			int FramePerSecond = _ttoi(token);

			std::map<tstring, CComponent*>::iterator iter;
			iter = m_mapSpriteComponent.find(tszName);
			if (iter == m_mapSpriteComponent.end())
			{
				LoadTexture(tszPath, tszPath);

				CComponent* pSprite = CSprite::Create();
				
				if (pSprite)
				{
					pSprite->SetComponentType(eComponentTypes_Sprite);
					dynamic_cast<CSprite*>(pSprite)->SetTexture(RSCMgr->GetTextureByName(tszPath));
					dynamic_cast<CSprite*>(pSprite)->SetAnimData(dynamic_cast<CSprite*>(pSprite)->ToAnimationState(tszAnimationState), OriginX, OriginY, PixelSizeX, PixelSizeY, FrameTotalCount, FramePerSecond);

					m_mapSpriteComponent.insert(std::make_pair(tszName, pSprite));
				}
			}
			else
			{
				CComponent* pSprite = iter->second;
				if(pSprite)
					dynamic_cast<CSprite*>(pSprite)->SetAnimData(dynamic_cast<CSprite*>(pSprite)->ToAnimationState(tszAnimationState), OriginX, OriginY, PixelSizeX, PixelSizeY, FrameTotalCount, FramePerSecond);
			}
			
		}
	}
	else
		return false;

	return true;
}

bool CResourceManager::LoadTexture(const TCHAR* name, const TCHAR* tszfilepath)
{
	std::string filepath;
#ifdef  UNICODE 

	char szMultibyte[MAX_PATH] = { 0, };
	int len = WideCharToMultiByte(CP_ACP, 0, tszfilepath, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, tszfilepath, -1, szMultibyte, len, NULL, NULL);
	filepath = szMultibyte;
#else
	filepath = tszfilepath;
#endif

	if (m_mapTexture.find(name) != m_mapTexture.end())
	{
		//char szMessage[MAX_PATH] = { 0, };
		//sprintf_s(szMessage, "%s is already exist\n", filepath.c_str());
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", szMessage, NULL);
		return false;
	}

	CTexture* pTex = CTexture::Create();
	pTex->SetTexture(IMG_LoadTexture(SDLRdr, filepath.c_str()));

	if (!pTex->GetTexture())
	{
		char szMessage[MAX_PATH] = { 0, };
		sprintf_s(szMessage, "%s load failed\n", filepath.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", szMessage, NULL);

		Safe_Release(pTex);
		return false;
	}

	pTex->SetPath(tszfilepath);

	m_mapTexture.insert(std::make_pair(name, pTex));

	return true;
	
}

SDL_Texture* CResourceManager::GetSDLTextureByName(const tstring& name)
{
	std::map<tstring, CTexture*>::iterator iter = m_mapTexture.find(name);
	if (iter != m_mapTexture.end())
	{
		if (iter->second)
			return iter->second->GetTexture();
	}

	return nullptr;
}

CTexture* CResourceManager::GetTextureByName(const tstring& name)
{
	std::map<tstring, CTexture*>::iterator iter = m_mapTexture.find(name);
	if (iter != m_mapTexture.end())
	{
		if (iter->second)
			return iter->second;
	}

	return nullptr;
}

CComponent* CResourceManager::GetSpriteComponent(const TCHAR* path)
{
	std::map<tstring, CComponent*>::iterator iter = m_mapSpriteComponent.find(path);
	if (iter != m_mapSpriteComponent.end())
	{
		if (iter->second)
			return iter->second;
	}

	return nullptr;
}
