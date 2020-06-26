#include "stdafx.h"
#include "Define.h"
#include "Function.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "UIManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "SingleTexture.h"
#include "Font.h"
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
	TTF_Quit();
	IMG_Quit();
}

bool CResourceManager::Init()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	m_Font = CFont::Create();
	m_Font->OpenFont( NORMALFONT, 14);

	//wchar_t buffer[MAX_PATH];
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

	if (false == LoadRootNameAndPath(_T("Resource/Data/UI/RootNameAndPath.csv")))
	{
		return false;
	}
		

	//if(false == LoadUIJSONFile(_T("Resource/Data/UI/MainMenu.json")))
		//return false;

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

bool CResourceManager::LoadScriptCSVFile(const wchar_t* file)
{
	std::wifstream wif(file);

	if (wif.is_open())
	{
		wif.imbue(std::locale("kor"));

		wchar_t wszBuf[1024] = { 0, };

		wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

		while (!wif.eof())
		{
			wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

			wchar_t seps[] = TEXT(",");
			wchar_t* token;
			wchar_t pStr[MAX_PATH];
			wchar_t* next_token = NULL;
			//wcscpy_s(pStr, wszBuf);
			_tcscpy_s(pStr, wszBuf);
			//token = wcstok_s(pStr, seps, &next_token);
			token = _tcstok_s(pStr, seps, &next_token);
			if (!token) return false;
			wchar_t tszIndex[MAX_PATH] = { 0, };
			_tcscpy_s(tszIndex, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszName[MAX_PATH] = { 0, };
			_tcscpy_s(tszName, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszMessage[MAX_PATH] = { 0, };
			_tcscpy_s(tszMessage, token);

			m_mapScript.insert(std::make_pair(tszName, tszMessage));
		}
	}
	else
		return false;

	return true;
}

bool CResourceManager::LoadSingleTextureCSVFile(const wchar_t* file)
{
	std::wifstream wif(file);

	if (wif.is_open())
	{
		wif.imbue(std::locale("kor"));

		wchar_t wszBuf[1024] = { 0, };

		wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

		while (!wif.eof())
		{
			wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

			wchar_t seps[] = TEXT(",");
			wchar_t *token;
			wchar_t pStr[MAX_PATH];
			wchar_t *next_token = NULL;
			//wcscpy_s(pStr, wszBuf);
			_tcscpy_s(pStr, wszBuf);
			//token = wcstok_s(pStr, seps, &next_token);
			token = _tcstok_s(pStr, seps, &next_token);
			if (!token) return false;
			wchar_t tszIndex[MAX_PATH] = { 0, };
			_tcscpy_s(tszIndex, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszName[MAX_PATH] = { 0, };
			_tcscpy_s(tszName, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszPath[MAX_PATH] = { 0, };
			_tcscpy_s(tszPath, token);

			LoadTexture(tszName, tszPath);
		}
	}
	else
		return false;

	return true;
}

bool CResourceManager::LoadSpriteTextureCSVFile(const wchar_t* file)
{
	std::wifstream wif(file);

	if (wif.is_open())
	{
		wif.imbue(std::locale("kor"));

		wchar_t wszBuf[1024] = { 0, };

		wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

		while (!wif.eof())
		{
			wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

			wchar_t seps[] = TEXT(",");
			wchar_t *token;
			wchar_t pStr[MAX_PATH];
			wchar_t *next_token = NULL;

			if (0 >= _tcsclen(wszBuf))
				continue;

			_tcscpy_s(pStr, wszBuf);
			token = _tcstok_s(pStr, seps, &next_token);
			if (!token) return false;
			wchar_t tszIndex[MAX_PATH] = { 0, };
			_tcscpy_s(tszIndex, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszName[MAX_PATH] = { 0, };
			_tcscpy_s(tszName, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszAnimationState[MAX_PATH] = { 0, };
			_tcscpy_s(tszAnimationState, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszPath[MAX_PATH] = { 0, };
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

			std::map<std::wstring, CComponent*>::iterator iter;
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

bool CResourceManager::LoadSerialSpriteTextureCSVFile(const wchar_t* file)
{
	std::wifstream wif(file);

	if (wif.is_open())
	{
		wif.imbue(std::locale("kor"));

		wchar_t wszBuf[1024] = { 0, };

		wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

		while (!wif.eof())
		{
			wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

			wchar_t seps[] = TEXT(",");
			wchar_t* token;
			wchar_t pStr[MAX_PATH];
			wchar_t* next_token = NULL;

			if (0 >= _tcsclen(wszBuf))
				continue;

			_tcscpy_s(pStr, wszBuf);
			token = _tcstok_s(pStr, seps, &next_token);
			if (!token) return false;
			wchar_t tszIndex[MAX_PATH] = { 0, };
			_tcscpy_s(tszIndex, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszName[MAX_PATH] = { 0, };
			_tcscpy_s(tszName, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszAnimationState[MAX_PATH] = { 0, };
			_tcscpy_s(tszAnimationState, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszPath[MAX_PATH] = { 0, };
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

			std::map<std::wstring, CComponent*>::iterator iter;
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

bool CResourceManager::LoadTexture(const wchar_t* name, const wchar_t* tszfilepath, bool loadimmediately /*= false*/)
{
	IMG_Init(IMG_INIT_PNG);

	std::string filepath;
#ifdef  UNICODE 
	filepath = WToM(tszfilepath);
#else
	filepath = tszfilepath;
#endif

	std::map<std::wstring, CTexture*>::iterator iter;
	iter = m_mapTexture.find(name);

	if (iter != m_mapTexture.end())
	{
		if (loadimmediately && (false == iter->second->GetLoaded()))
		{
			CTexture* pTex = iter->second;
			if (pTex)
			{
				pTex->SetTexture(IMG_LoadTexture(SDLRdr, filepath.c_str()));
				if (pTex->GetTexture())
				{
					pTex->SetLoaded(true);
				}
				else
				{
					errormsg(filepath.c_str());
					Safe_Release(pTex);
					return false;
				}
			}
		}
	}
	else
	{
		CTexture* pTex = CTexture::Create();

		if (loadimmediately)
		{
			pTex->SetTexture(IMG_LoadTexture(SDLRdr, filepath.c_str()));
			if (pTex->GetTexture())
			{
				pTex->SetLoaded(true);
			}
			else
			{
				errormsg(filepath.c_str());
				Safe_Release(pTex);
				return false;
			}
		}

		pTex->SetName(name);
		pTex->SetPath(tszfilepath);
		m_mapTexture.insert(std::make_pair(name, pTex));
	}
	
	return true;
	
}

bool CResourceManager::LoadRootNameAndPath(const wchar_t* file)
{
	std::wifstream wif(file);

	if (wif.is_open())
	{
		wif.imbue(std::locale("kor"));

		wchar_t wszBuf[1024] = { 0, };

		wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

		while (!wif.eof())
		{
			wif.getline((WCHAR*)wszBuf, _countof(wszBuf));

			wchar_t seps[] = TEXT(",");
			wchar_t* token;
			wchar_t pStr[MAX_PATH];
			wchar_t* next_token = NULL;

			if (0 >= _tcsclen(wszBuf))
				continue;

			_tcscpy_s(pStr, wszBuf);
			token = _tcstok_s(pStr, seps, &next_token);
			if (!token) return false;
			wchar_t tszIndex[MAX_PATH] = { 0, };
			_tcscpy_s(tszIndex, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszName[MAX_PATH] = { 0, };
			_tcscpy_s(tszName, token);

			token = _tcstok_s(NULL, seps, &next_token);
			if (!token) return false;
			wchar_t tszPath[MAX_PATH] = { 0, };
			_tcscpy_s(tszPath, token);

			m_mapNameAndPath.insert(std::make_pair(tszName, tszPath));
		}
	}
	else
		return false;

	return true;
}

bool CResourceManager::LoadNamingTextureJSONFile(const wchar_t* tszfilepath)
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
			errormsg(filepath.c_str());
			return false;
		}
		
		Json::Value root = value["Root"];

		int rootsize = root.size();
		for (int i = 0; i < rootsize; ++i)
		{
			CComponent* pSingleTexture = CSingleTexture::Create();

			std::wstring Name = MToW(root[i][0].asString().c_str());
			dynamic_cast<CSingleTexture*>(pSingleTexture)->SetName(Name);

			std::wstring SingleTextureName = MToW(root[i][1].asString().c_str());
			CTexture* pTexture = GetTextureByName(SingleTextureName);

			if (!pTexture)
			{
				errormsg(root[i][1].asString().c_str());
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

			dynamic_cast<CSingleTexture*>(pSingleTexture)->SetShow(false);
			dynamic_cast<CSingleTexture*>(pSingleTexture)->Set(srcRect, destRect, eRenderLayer_Object, pTexture);

			m_mapNamingTexture.insert(std::make_pair(Name, pSingleTexture));
		}
	}

	return true;
}

bool CResourceManager::LoadUIJSONFile(const wchar_t* tszfilepath)
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
			errormsg(filepath.c_str());

			return false;
		}
		
		UIMGR->ParseUI(value);		
	}

	return true;
}

bool CResourceManager::LoadUIJSONFilebyName(const wchar_t* tszname)
{
	std::map<std::wstring, std::wstring>::iterator iter = m_mapNameAndPath.find(tszname);

	if (iter != m_mapNameAndPath.end())
	{
		if (LoadUIJSONFile(iter->second.c_str()))
			return true;
	}
	
	return false;
}


CTexture* CResourceManager::GetTextureByName(const std::wstring& name)
{
	std::map<std::wstring, CTexture*>::iterator iter = m_mapTexture.find(name);
	if (iter != m_mapTexture.end())
	{
		CTexture* pTexture = iter->second;
		if (pTexture)
		{
			return pTexture;
		}		
	}

	return nullptr;
}

CComponent* CResourceManager::GetSpriteComponent(const wchar_t* path)
{
	std::map<std::wstring, CComponent*>::iterator iter = m_mapSpriteComponent.find(path);
	if (iter != m_mapSpriteComponent.end())
	{
		if (iter->second)
			return iter->second;
	}

	return nullptr;
}

CComponent* CResourceManager::GetNamingTextureByName(const std::wstring& name)
{
	CComponent* pNamingTexture = NULL;

	std::map<std::wstring, CComponent*>::iterator iter = m_mapNamingTexture.find(name);
	if (iter != m_mapNamingTexture.end())
	{
		pNamingTexture = iter->second;
	}
	return pNamingTexture;
}

CFont* CResourceManager::GetFont()
{
	return m_Font;
}
