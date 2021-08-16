/*!
 * \class classname
 *
 * \brief 
 *
 * \author mook
 * \date 7¿ù 2018
 */

#pragma once

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

	//CSV
	bool LoadScriptCSVFile(const wchar_t* file);
	bool LoadSingleTextureCSVFile(const wchar_t* file);
	bool LoadSpriteTextureCSVFile(const wchar_t* file);
	bool LoadSerialSpriteTextureCSVFile(const wchar_t* file);

	bool LoadTexture(const wchar_t* name, const wchar_t* tszfilepath);
	bool LoadRootNameAndPath(const wchar_t* file);

	//JSON
	bool LoadNamingTextureJSONFile(const wchar_t* tszfilepath);
	bool LoadUIJSONFile(const wchar_t* tszfilepath);
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
	std::map<std::wstring, std::wstring>	m_mapNameAndPath;//UI RootName And Path

	CFont*			m_Font;
};

#define RSCMgr	CResourceManager::GetInstance()
#define RSFONT	CResourceManager::GetInstance()->GetFont()
