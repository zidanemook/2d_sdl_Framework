#include "stdafx.h"
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

#define FILENAMEANDPATH "filenameandpath.bin"

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
	
	if (false == InputFileNameAndPath())
	{
		FindAndResistFiles(L"Resource/");
	}

	if (false == LoadScriptCSVFile(_T("Script.csv")))
		return false;

	if (false == LoadSingleTextureCSVFile(_T("Resource/Data/SingleTexture.csv")))
		return false;

	//if (false == LoadSpriteTextureCSVFile(_T("Resource/Data/SpriteTexture.csv")))
	//	return false;
	if (false == LoadSerialSpriteTextureCSVFile(_T("Resource/Data/SpriteTexture.csv")))
		return false;

	if (false == LoadNamingTextureJSONFile(_T("Resource/Data/UI/NamingTexture.json")))
		return false;

	


		

	//Resource 폴더의 파일들을 알아서 m_mapNameAndPath 에 추가되게 하자
	//if (false == LoadRootNameAndPath(_T("Resource/Data/UI/RootNameAndPath.csv")))
	//{
	//	return false;
	//}
		

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

	OutputFileNameAndPath();
}

void CResourceManager::FindAndResistFiles(const wchar_t* wszPath)
{
	std::wstring wstrFindPath = wszPath + std::wstring(L"*.*");

	WIN32_FIND_DATAW _find_data;
	HANDLE hFind = ::FindFirstFile(wstrFindPath.c_str(), &_find_data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (_find_data.cFileName[0] == '.')
					continue;

				std::wstring _path = wszPath + std::wstring(_find_data.cFileName) + std::wstring(L"/");
				m_vecFolders.push_back(_path);

				FindAndResistFiles(_path.c_str());
			}
			else
			{
				std::wstring _path = wszPath + std::wstring(_find_data.cFileName);
				m_mapNameAndPath.insert(std::make_pair(std::wstring(_find_data.cFileName), _path));
			}

		} while (::FindNextFile(hFind, &_find_data) != 0);

		::FindClose(hFind);
	}
}

//void CResourceManager::FindAndResistFolders(const wchar_t* wszPath)
//{
//	std::wstring wstrFindPath = wszPath + std::wstring(L"*.*");
//
//	WIN32_FIND_DATAW _find_data;
//	HANDLE hFind = ::FindFirstFile(wstrFindPath.c_str(), &_find_data);
//	if (hFind != INVALID_HANDLE_VALUE)
//	{
//		do
//		{
//			if (_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
//			{
//				if (_find_data.cFileName[0] == '.')
//					continue;
//
//				std::wstring _path = wszPath + std::wstring(_find_data.cFileName) + std::wstring(L"/");
//				m_vecFolders.push_back( _path);
//
//				FindAndResistFolders(_path.c_str());
//			}
//
//		} while (::FindNextFile(hFind, &_find_data) != 0);
//
//		::FindClose(hFind);
//	}
//}

bool CResourceManager::InputFileNameAndPath()
{
	FILE* file=NULL;
	fopen_s(&file, FILENAMEANDPATH, "r");
	char* buffer = NULL;
	if (NULL != file)
	{
		int size = 0;
		fseek(file, 0, SEEK_END); // 파일 포인터를 파일의 끝으로 이동시킴
		size = ftell(file);

		buffer = new char[size+1];
		memset(buffer, 0, size + 1);
		fseek(file, 0, SEEK_SET);
		
		fread(buffer, size, 1, file);

	

		char seps[] = (",");
		char* token = seps;
		char pStr[MAX_PATH] = { 0, };
		char* next_token = buffer;
		
		while (next_token != NULL)
		{
			token = strtok_s(next_token, seps, &next_token);

			if (!token)
				break;

			char szKey[MAX_PATH] = { 0, };
			strcpy_s(szKey, token);

			token = strtok_s(next_token, seps, &next_token);
			char szFilePaht[MAX_PATH] = { 0, };
			strcpy_s(szFilePaht, token);

			m_mapNameAndPath.insert(std::make_pair(MToW(szKey), MToW(szFilePaht)));
		}

		Safe_Delete(buffer);
		return true;
	}
	else
		return false;
}

void CResourceManager::OutputFileNameAndPath()
{
	// Get module path name
	//wchar_t _cliexepath[_MAX_PATH];
	//::GetModuleFileName(NULL, _cliexepath, _MAX_PATH);

	//std::wstring cliexepath = _cliexepath;
	//size_t slashpos = cliexepath.find_last_of(L"/");
	//std::wstring filenameandpath = cliexepath.substr(0, slashpos);

	FILE* file = NULL;
	fopen_s(&file, FILENAMEANDPATH, "w");
	
	if (NULL != file)
	{

		std::map<std::wstring, std::wstring>::iterator iter = m_mapNameAndPath.begin();
		for (iter; iter != m_mapNameAndPath.end(); ++iter)
		{
			fprintf(file, "%s,%s,", WToM(iter->first.c_str()).c_str(), WToM(iter->second.c_str()).c_str());
		}
		
		fclose(file);
	}
	else
	{
		log("%s write failed\n", FILENAMEANDPATH);
	}

	//FILENAMEANDPATH
}

std::wstring CResourceManager::FindPath(const wchar_t* filename)
{
	std::map<std::wstring, std::wstring>::iterator iter = m_mapNameAndPath.find(filename);

	if (iter != m_mapNameAndPath.end())
		return iter->second;
	else
	{
		if (true == m_vecFolders.empty())
		{
			FindAndResistFiles(L"Resource/");
		}

		//m_vecFolders 사용해서 파일이 있는곳을 알아내서 반환
		std::wstring _pathfilename;
		for (size_t i = 0; i != m_vecFolders.size(); ++i)
		{
			_pathfilename = m_vecFolders[i] + filename;

			SDL_RWops* file = SDL_RWFromFile(WToM(_pathfilename.c_str()).c_str(), "r+b");
			if (file)
			{
				m_mapNameAndPath.insert(std::make_pair(filename, _pathfilename));
				return _pathfilename;
			}
		}

		log("%s not exist\n", WToM(_pathfilename.c_str()).c_str());
		return std::wstring(L"");
	}
	
}

bool CResourceManager::LoadScriptCSVFile(const wchar_t* file)
{
	std::wstring filepath = FindPath(file);

	std::wifstream wif(filepath.c_str());

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

bool CResourceManager::LoadTexture(const wchar_t* name, const wchar_t* tszfilepath)
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
		/*if (false == iter->second->GetLoaded())
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
		}*/
		log("duplicate %s (LoadTexture)\n", filepath.c_str());

	}
	else
	{
		CTexture* pTex = CTexture::Create();

		pTex->SetTexture(IMG_LoadTexture(SDLRdr, filepath.c_str()));
		if (pTex->GetTexture())
		{
			pTex->SetLoaded(true);
		}
		else
		{
			log("%s load failed(IMG_LoadTexture)\n", filepath.c_str() );
			Safe_Release(pTex);
			return false;
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
			log("%s load failed (LoadNamingTextureJSONFile)\n", filepath.c_str());
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
				log(root[i][1].asString().c_str());
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

CUIWnd* CResourceManager::LoadUIJSONFile(const wchar_t* tszfilepath)
{
	std::wstring wstrfilepath = RSCMgr->FindPath(tszfilepath);

	std::string strfilepath;
	strfilepath = WToM(wstrfilepath.c_str());

	std::ifstream ifs(strfilepath);

	if (ifs.is_open())
	{
		ifs.imbue(std::locale("kor"));

		Json::Value value;
		Json::Reader reader;

		if (false == reader.parse(ifs, value))
		{
			log("%s load failed (LoadUIJSONFile)\n", strfilepath.c_str());

			return false;
		}
		
		return UIMGR->ParseUI(value);		
	}

	return NULL;
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
