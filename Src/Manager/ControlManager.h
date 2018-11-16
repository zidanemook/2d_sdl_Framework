#pragma once
#include "define.h"

class CControlManager
{
private:
	static CControlManager*		m_pInst;

public:
	static CControlManager* GetInst(void)
	{
		if(m_pInst == NULL)
			m_pInst = new CControlManager;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}
public:
	CControlManager(void);
	~CControlManager(void);

public:
	void Update();

};

#define CTRLMGR CControlManager::GetInst()