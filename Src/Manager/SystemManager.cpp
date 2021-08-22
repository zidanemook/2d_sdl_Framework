#include "stdafx.h"
#include "SystemManager.h"
#include <shlobj_core.h>//SHGetKnownFolderPath
#include <fstream>
#include "json.h"

#define CONFIGFILE L"config.json"
#define GAMENAME L"2DFramework"

CSystemManager* CSystemManager::m_pInst = nullptr;

CSystemManager::CSystemManager()
	: m_iWidth(DEFAULT_SCREEN_WIDTH), m_iHeight(DEFAULT_SCREEN_HEIGHT)
{
}


CSystemManager::~CSystemManager()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

bool CSystemManager::Init(const char* title, int xpos, int ypos, bool fullscreen)
{
	bool bResult = false;

	if (fullscreen)
	{
		m_iFlag = SDL_WINDOW_FULLSCREEN;
	}

	//load config file

	if (true == LoadConfig(GetConfigPath().c_str()))
	{		
	}
	else
	{
		log("LoadConfig failed\n");
	}


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//wprintf(L"Sub system initialized\n");

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, m_iWidth, m_iHeight, m_iFlag);
		if (!m_pWindow)
		{
			log("Window failed\n");
		}
		else
		{
			bResult = true;
		}
			
	}
	else
	{
		log( "Sub system failed\n" );
	}

	return bResult;
}

SDL_Window * CSystemManager::GetWindow()
{
	return m_pWindow;
}

int CSystemManager::GetWindowWidth()
{
	return m_iWidth;
}

int CSystemManager::GetWindowHeight()
{
	return m_iHeight;
}

bool CSystemManager::LoadConfig(const wchar_t* wszfilepath)
{
	std::ifstream ifs(WToM(GetConfigPath().c_str()));

	if (ifs.is_open())
	{
		ifs.imbue(std::locale("kor"));

		Json::Value value;
		Json::Reader reader;

		if (false == reader.parse(ifs, value))
		{
			log("%s load failed (LoadNamingTextureJSONFile)\n", WToM(GetConfigPath().c_str()).c_str());
			return false;
		}

		m_iWidth = value["screen_width"].asInt();
		m_iHeight = value["screen_height"].asInt();
		m_iFlag = value["screen_flag"].asInt();

		return true;

		ifs.close();
	}

	return false;
}

bool CSystemManager::SaveConfig()
{
	
	std::ofstream ofs(WToM(GetConfigPath().c_str()));

	Json::Value value;
	value["screen_width"] = m_iWidth;
	value["screen_height"] = m_iHeight;
	value["screen_flag"] = m_iFlag;

	Json::StyledWriter writer;
	std::string data = writer.write(value);

	if(ofs.is_open())
	{
		ofs << data.c_str();

		return true;
	}
	
	return false;
}

std::wstring CSystemManager::GetConfigPath()
{
	wchar_t* my_documents = NULL;
	HRESULT result = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &my_documents);
	if (S_OK != result)
		log("SHGetKnownFolderPath failed\n");

	wchar_t wstConfigpath[MAX_PATH];
	wsprintf(wstConfigpath, L"%s\\%s", my_documents, GAMENAME);
	CoTaskMemFree(my_documents);

	//check folder exist
	DWORD ftyp = GetFileAttributes(wstConfigpath);
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		_wmkdir(wstConfigpath);
	}
	
	

	std::wstring path = wstConfigpath;
	path += L"\\";
	path += CONFIGFILE;

	return path;
}
