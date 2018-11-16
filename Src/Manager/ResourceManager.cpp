#include "stdafx.h"
#include "Define.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "Texture.h"
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
	
	if (false == LoadTextureCSVFile(_T("Resource/Data/SingleTexture.csv")))
		return false;

	return true;
}

void CResourceManager::Destroy()
{
	for_each(m_mapTexture.begin(), m_mapTexture.end(), ReleaseMapElement());
	m_mapTexture.clear();
}

bool CResourceManager::LoadTextureCSVFile(const TCHAR* file)
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

			//token = wcstok_s(NULL, seps, &next_token);
			//if (!token) return;
			//int iGrade = _wtoi(token);
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
		char szMessage[MAX_PATH] = { 0, };
		sprintf_s(szMessage, "%s is already exist\n", filepath.c_str());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", szMessage, NULL);
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
