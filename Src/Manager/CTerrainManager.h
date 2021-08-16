#pragma once

/*!
 * \class classname
 *
 * \brief
 *
 * \author mook
 * \date 8¿ù 2021
 */

class CTerrainManager
{
private:
	static CTerrainManager*		m_pInst;

public:
	static CTerrainManager* GetInst(void)
	{
		if (m_pInst == NULL)
			m_pInst = new CTerrainManager;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}

public:
	CTerrainManager();
	~CTerrainManager();

public:
	void Init();
	void Update();
};

#define TERMGR CTerrainManager::GetInst()