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
	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	SDL_Window * GetWindow();
	int			GetWindowWidth();
	int			GetWindowHeight();
	
private:
	SDL_Window * m_pWindow;
	//SDL_Renderer *m_pRenderer;
	int	m_iWidth;
	int m_iHeight;
};

#define SYSMGR	CSystemManager::GetInstance()
