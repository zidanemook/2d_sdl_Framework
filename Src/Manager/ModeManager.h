#pragma once

#include <map>

class CBaseMode;

class CModeManager 
{
private:
	static CModeManager*		m_pInst;

public:
	static CModeManager* GetInstance(void)
	{
		if(m_pInst == nullptr)
			m_pInst = new CModeManager;

		return m_pInst;
	}

	void DestroyInstance(void)
	{
		Destroy();

		delete m_pInst;
		m_pInst = nullptr;
	}

private:
	typedef std::map< int, CBaseMode* > MODEMAP;

public:
	CModeManager();
	~CModeManager();

	bool Create();
	void Destroy();
	void Update();
	void DrawUI();

	bool AddMode( const int iModeID, CBaseMode* const pMode );

	bool ChangeMode( const int iModeID, bool bForceChange = false );
	CBaseMode* GetMode( const int iModeID );
	CBaseMode* GetCurrentMode() { return m_pCurMode; }
	
private:
	MODEMAP m_mapMode;
	CBaseMode* m_pPrevMode;
	CBaseMode* m_pCurMode;
	CBaseMode* m_pNextMode;
};

#define ModeMgr CModeManager::GetInstance()
