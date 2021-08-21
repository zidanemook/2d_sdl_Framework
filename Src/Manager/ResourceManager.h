/*!
 * \class classname
 *
 * \brief 
 *
 * \author mook
 * \date 7¿ù 2018
 */

#pragma once

typedef struct _stFileNameAndPath
{
	std::string filename;
	std::string filepath;

}stFileNameAndPath;

class CUIWnd;
class CTexture;
class CComponent;
class CFont;
class CResourceManager
{
private:
	static CResourceManager*		m_pInst;

public:
	static CResourceManager* GetInstance(void)
	{
		if (m_pInst == nullptr)
			m_pInst = new CResourceManager;

		return m_pInst;
	}

	void DestroyInstance(void)
	{
		Destroy();
		delete m_pInst;
		m_pInst = nullptr;
	}

public:
	CResourceManager();
	~CResourceManager();

public:
	bool Init();
	void Destroy();

	void FindAndResistFiles(const wchar_t* wszPath);
	//void FindAndResistFolders(const wchar_t* wszPath);
	bool InputFileNameAndPath();
	void OutputFileNameAndPath();
	std::wstring FindPath(const wchar_t* filename);

	//CSV
	bool LoadScriptCSVFile(const wchar_t* file);
	bool LoadSingleTextureCSVFile(const wchar_t* file);
	bool LoadSpriteTextureCSVFile(const wchar_t* file);
	bool LoadSerialSpriteTextureCSVFile(const wchar_t* file);

	bool LoadTexture(const wchar_t* name, const wchar_t* tszfilepath);
	bool LoadRootNameAndPath(const wchar_t* file);

	//JSON
	bool LoadNamingTextureJSONFile(const wchar_t* tszfilepath);
	CUIWnd* LoadUIJSONFile(const wchar_t* tszfilepath);
	bool LoadUIJSONFilebyName(const wchar_t* tszname);

	CTexture*		GetTextureByName(const std::wstring& name);
	CComponent*		GetSpriteComponent(const wchar_t* path);
	CComponent*		GetNamingTextureByName(const std::wstring& name);
	CFont*			GetFont();


private:
	

private:

	std::map<std::wstring, std::wstring>	m_mapScript;
	std::map<std::wstring, CTexture*>		m_mapTexture;//Name or Path, Texture
	std::map<std::wstring, CComponent*>		m_mapSpriteComponent;//For Sprite animation
	std::map<std::wstring, CComponent*>		m_mapNamingTexture;
	std::vector<std::wstring>				m_vecFolders;// to find file //if file not registerd use this to find file
	std::map<std::wstring, std::wstring>	m_mapNameAndPath;// fileName And Path

	CFont*			m_Font;
};

#define RSCMgr	CResourceManager::GetInstance()
#define RSFONT	CResourceManager::GetInstance()->GetFont()
