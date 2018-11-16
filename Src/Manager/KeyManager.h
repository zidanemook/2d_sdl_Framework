#pragma once
#include "define.h"

typedef struct tagKeyBind
{
	BYTE		FirstVirtualKey;
	BYTE		SecondVirtualKey;
}stKeyBind;

class CKeyManager
{
private:
	static CKeyManager*		m_pInst;

	BYTE				m_NowKeyState[ 256 ];
	BYTE				m_LastKeyState[ 256 ];

	stKeyBind			m_arrKeyBind[eKeyFunc_Max];
public:

	void UpdateKeyBoardState();
	bool CheckInputKey( BYTE byInputKey, DWORD dwInputFlag );

	void ClearKeyState();

public:
	static CKeyManager* GetInst(void)
	{
		if(m_pInst == NULL)
			m_pInst = new CKeyManager;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}

public:
	void Init();
	bool CheckKey(eKeyFunc eKey, DWORD state);

private:
	CKeyManager(void);

public:
	~CKeyManager(void);
};

#define KEYMGR CKeyManager::GetInst()