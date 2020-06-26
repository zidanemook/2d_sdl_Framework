#pragma once
#include "define.h"

class CEditorManager
{
private:
	static CEditorManager* m_pInst;

public:
	static CEditorManager* GetInst(void)
	{
		if (m_pInst == NULL)
			m_pInst = new CEditorManager;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}
public:
	CEditorManager(void);
	~CEditorManager(void);

public:
	void Update();

};

#define EDITMGR CEditorManager::GetInst()

