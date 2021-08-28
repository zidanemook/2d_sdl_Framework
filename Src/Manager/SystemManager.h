#pragma once



class CSystemManager
{
private:
	static CSystemManager*		m_pInst;

public:
	static CSystemManager* GetInstance(void)
	{
		if (m_pInst == NULL)
			m_pInst = new CSystemManager;

		return m_pInst;
	}

	void DestroyInstance(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}

public:
	CSystemManager();
	~CSystemManager();

public:
	bool Init(const char* title, int xpos, int ypos, bool fullscreen);
	bool ChangeResolution();

	SDL_Window * GetWindow();
	int			GetWindowWidth();
	void		SetWindowWidth(int width);
	int			GetWindowHeight();
	void		SetWindowHeight(int Height);
	bool		LoadConfig(const wchar_t* wszfilepath);
	bool		SaveConfig();
	std::wstring	GetConfigPath();

private:
	SDL_Window * m_pWindow;
	//SDL_Renderer *m_pRenderer;
	int	m_iWidth;
	int m_iHeight;
	bool m_bResolutionChange;
	int m_iFlag;
	std::string m_title;
};

#define SYSMGR	CSystemManager::GetInstance()
