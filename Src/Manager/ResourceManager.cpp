#include "stdafx.h"
#include "Define.h"
#include "Function.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "SingleTexture.h"
#include "Component.h"
#include <atlstr.h>
#include <fstream>
#include "json.h"//https://github.com/open-source-parsers/jsoncpp/wiki

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
	
	if (false == LoadScriptCSVFile(_T("Resource/Data/UI/Script.csv")))
		return false;

	if (false == LoadSingleTextureCSVFile(_T("Resource/Data/SingleTexture.csv")))
		return false;

	//if (false == LoadSpriteTextureCSVFile(_T("Resource/Data/SpriteTexture.csv")))
	//	return false;
	if (false == LoadSerialSpriteTextureCSVFile(_T("Resource/Data/SpriteTexture.csv")))
		return false;

	if (false == LoadNamingTextureJSONFile(_T("Resource/Data/UI/NamingTexture.json")))
		return false;



	return true;
}

void CResourceManager::Destroy()
{
	
	for_each(m_mapNamingTexture.begin(), m_mapNamingTexture.end(), ReleaseMapElement());
	m_mapNamingTexture.clear();

	for_each(m_mapSpriteComponent.begin(), m_mapSpriteComponent.end(), ReleaseMapElement());
	m_mapSpriteComponent.clear();

	for_each(m_mapTexture.begin(), m_mapTexture.end(), ReleaseMapElement());
	m_mapTexture.clear();
}

bool CResourceManager::LoadScriptCSVFile(const TCHAR* file)
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
			TCHAR* token;
			TCHAR pStr[MAX_PATH];
			TCHAR* next_token = NULL;
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
			TCHAR tszMessage[MAX_PATH] = { 0, };
			_tcscpy_s(tszMessage, token);

			m_mapScript.insert(std::make_pair(tszName, tszMessage));
		}
	}
	else
		return false;

	return true;
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

			if (0 >= _tcsclen(tszBuf))
				continue;

			_tcscpy_s(pStr, tszBuf);
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
			TCHAR tszAnimationState[MAX_PATH] = { 0, };
			_tcscpy_s(tszAnimationState, token);

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

bool CResourceManager::LoadSerialSpriteTextureCSVFile(const TCHAR* file)
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
			TCHAR* token;
			TCHAR pStr[MAX_PATH];
			TCHAR* next_token = NULL;

			if (0 >= _tcsclen(tszBuf))
				continue;

			_tcscpy_s(pStr, tszBuf);
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
			TCHAR tszAnimationState[MAX_PATH] = { 0, };
			_tcscpy_s(tszAnimationState, token);

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
				if (pSprite)
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
	filepath = WToM(tszfilepath);
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

bool CResourceManager::LoadNamingTextureJSONFile(const TCHAR* tszfilepath)
{
	std::string filepath;
	filepath = WToM(tszfilepath);
	
	std::ifstream ifs(filepath);

	if (ifs.is_open())
	{
		ifs.imbue(std::locale("kor"));

		Json::Value value;
		Json::Reader reader;

		if (false == reader.parse(ifs, value))
		{
			char szMessage[MAX_PATH] = { 0, };
			sprintf_s(szMessage, "%s load failed\n", filepath.c_str());
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", szMessage, NULL);
			return false;
		}
		
		Json::Value root = value["root"];

		int rootsize = root.size();
		for (int i = 0; i < rootsize; ++i)
		{
			CComponent* pSingleTexture = CSingleTexture::Create();

			std::wstring Name = MToW(root[i][0].asString());
			dynamic_cast<CSingleTexture*>(pSingleTexture)->SetName(Name);

			std::wstring SingleTextureName = MToW(root[i][1].asString());
			CTexture* pTexture = GetTextureByName(SingleTextureName);

			if (!pTexture)
			{
				char szMessage[MAX_PATH] = { 0, };
				sprintf_s(szMessage, "%s find fail plz add to singletexture.csv\n", root[i][1].asString().c_str());
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", szMessage, NULL);
				return false;
			}
			//dynamic_cast<CSingleTexture*>(pSingleTexture)->SetTexture(pTexture);

			int iStart_Pos_X = root[i][2].asInt();
			int iStart_Pos_Y = root[i][3].asInt();
			int iEnd_Pos_X = root[i][4].asInt();
			int iEnd_Pos_Y = root[i][5].asInt();

			SDL_Rect srcRect;
			srcRect.h = iEnd_Pos_Y - iStart_Pos_Y;
			srcRect.w = iEnd_Pos_X - iStart_Pos_X;
			srcRect.x = iStart_Pos_X;
			srcRect.y = iStart_Pos_Y;

			SDL_Rect destRect;
			destRect.h = srcRect.h;
			destRect.w = srcRect.w;
			destRect.x = 0;
			destRect.y = 0;

			dynamic_cast<CSingleTexture*>(pSingleTexture)->SetShow(true);
			dynamic_cast<CSingleTexture*>(pSingleTexture)->Set(srcRect, destRect, eRenderLayer_UI, pTexture);

			m_mapNamingTexture.insert(std::make_pair(Name, pSingleTexture));
		}
	}

	return true;
}

bool CResourceManager::LoadUIJSONFile(const TCHAR* tszfilepath)
{



	return false;
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
