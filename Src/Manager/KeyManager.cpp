#include "stdafx.h"
#include "KeyManager.h"
#include <Winuser.h>

CKeyManager*		CKeyManager::m_pInst = NULL;
CKeyManager::CKeyManager(void)
{
	memset( m_NowKeyState, 0, sizeof( m_NowKeyState ) );
	memset( m_LastKeyState, 0, sizeof( m_LastKeyState ) );
}

CKeyManager::~CKeyManager(void)
{
}

void CKeyManager::UpdateKeyBoardState()
{
	//// 입력 초기화
	memset( m_NowKeyState, 0, sizeof( m_NowKeyState ) );

	if( GetKeyboardState( m_NowKeyState ) )	
	{
		for( UINT nState = 0; nState < 256 ; ++nState )
		{
			if( m_NowKeyState[ nState ] & HOLDKEY )
			{
				if( ( m_LastKeyState[ nState ] & HOLDKEY ) == false )
				{
					m_NowKeyState[ nState ] |= PUSHKEY;
				}
			}
			else
			{
				if( m_LastKeyState[ nState ] & HOLDKEY )
				{
					m_NowKeyState[ nState ] = PULLKEY;
				}
				else
				{
					m_NowKeyState[ nState ] = FREEKEY;
				}
			}

			m_LastKeyState[ nState ] = m_NowKeyState[ nState ];
		}
	}
	/*memset( m_NowKeyState, 0, sizeof( m_NowKeyState ) );

	if( GetKeyboardState( m_NowKeyState ) )	
	{
		for( int nState = 0; nState < 256 ; ++nState )
		{
			if( m_NowKeyState[ nState ] & HOLDKEY )
			{
				if( ( m_LastKeyState[ nState ] & HOLDKEY ) == false )
				{
					m_NowKeyState[ nState ] |= PUSHKEY;
				}
			}
			else
			{
				if( m_LastKeyState[ nState ] & HOLDKEY )
				{
					m_NowKeyState[ nState ] = PULLKEY;
				}
				else
				{
					m_NowKeyState[ nState ] = FREEKEY;
				}
			}

			m_LastKeyState[ nState ] = m_NowKeyState[ nState ];
		}
	}*/
}

bool CKeyManager::CheckInputKey( BYTE byInputKey, DWORD dwInputFlag )
{
	if( byInputKey < 256 && m_NowKeyState[ byInputKey ] & dwInputFlag )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CKeyManager::ClearKeyState()
{
	memset( m_NowKeyState, 0, sizeof( m_NowKeyState ) );
	memset( m_LastKeyState, 0, sizeof( m_LastKeyState ) );
}

void CKeyManager::Init()
{
	//유저가 저장한 키값이 없다면
	m_arrKeyBind[eKeyFunc_MoveLeft].FirstVirtualKey = 'A';
	m_arrKeyBind[eKeyFunc_MoveRight].FirstVirtualKey = 'D';
	m_arrKeyBind[eKeyFunc_MoveUp].FirstVirtualKey = 'W';
	m_arrKeyBind[eKeyFunc_MoveDown].FirstVirtualKey = 'S';
	m_arrKeyBind[eKeyFunc_Interact].FirstVirtualKey = VK_LBUTTON;
	m_arrKeyBind[eKeyFunc_Defence].FirstVirtualKey = VK_RBUTTON;
	m_arrKeyBind[eKeyFunc_Enter].FirstVirtualKey = VK_RETURN;
	m_arrKeyBind[eKeyFunc_Esc].FirstVirtualKey = VK_ESCAPE;
	//유저가 저장한 키값이 있다면 파싱할것. 내문서에 저장할것
}

bool CKeyManager::CheckKey(eKeyFunc eKey, DWORD state)
{
	if (true == CheckInputKey(m_arrKeyBind[eKey].FirstVirtualKey, state)
		|| true == CheckInputKey(m_arrKeyBind[eKey].SecondVirtualKey, state))
	{
		return true;
	}
	return false;
}
