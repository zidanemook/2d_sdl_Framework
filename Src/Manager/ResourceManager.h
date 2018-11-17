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
	bool LoadSingleTextureCSVFile(const TCHAR* file);
	bool LoadSpriteTextureCSVFile(const TCHAR* file);
	bool LoadTexture(const TCHAR* name, const TCHAR* tszfilepath);
	SDL_Texture*	GetSDLTextureByName(const tstring& name);
	CTexture*		GetTextureByName(const tstring& name);
	CComponent*		GetSpriteComponent(const TCHAR* path);

private:
	std::map<tstring, CTexture*>		m_mapTexture;//Name or Path, Texture
	std::map<tstring, CComponent*>		m_mapSpriteComponent;
};

#define RSCMgr	CResourceManager::GetInstance()
