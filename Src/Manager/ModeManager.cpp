#include "stdafx.h"
#include "ModeManager.h"
#include "BaseMode.h"
#include "FadeSystem.h"

CModeManager* CModeManager::m_pInst = nullptr;

CModeManager::CModeManager()
{
	m_pCurMode = NULL;
	m_pNextMode = NULL;
}

CModeManager::~CModeManager()
{
}

bool CModeManager::Create()
{
	return true;
}

void CModeManager::Destroy()
{
	for( MODEMAP::iterator it = m_mapMode.begin(); it != m_mapMode.end(); )
	{
		if( NULL != (*it).second )
			delete (*it).second;
		it = m_mapMode.erase( it );
	}
	m_mapMode.clear();
}

bool CModeManager::AddMode( const int iModeID, CBaseMode* const pMode )
{
	if( NULL == pMode )
		return false;

	CBaseMode* pSetMode = GetMode( iModeID );
	if( pSetMode )
		return false;

	m_mapMode.insert( std::make_pair( iModeID, pMode ) );

	return true;
}

bool CModeManager::ChangeMode( const int iModeID, bool bForceChange )
{
	CBaseMode* pChangeMode = GetMode( iModeID );
	if( NULL == pChangeMode )
		return false;

	if( m_pCurMode == pChangeMode && false == bForceChange )
		return false;

	if( m_pCurMode == NULL )
	{
		m_pCurMode = pChangeMode;
		m_pCurMode->Open();

		m_pCurMode->m_eModeState = eModeState_Open;
		CFadeSystem::GetInst()->StartFade(eFadeStage_In, m_pCurMode->GetFadeOpenTime() );
		return true;
	}

	if( m_pCurMode->m_eModeState == eModeState_Close )
		return false;;

	m_pCurMode->Close();
	m_pNextMode = pChangeMode;

	return true;
}

CBaseMode* CModeManager::GetMode( const int iModeID )
{
	MODEMAP::iterator it = m_mapMode.find( iModeID );
	if( it != m_mapMode.end() )
		return (*it).second;

	return NULL;
}

void CModeManager::Update()
{
	if( NULL == m_pCurMode )
		return;

	CFadeSystem::GetInst()->OnRender();

	if( m_pCurMode->m_eModeState != eModeState_Closed )
		m_pCurMode->Update();

	if( m_pCurMode->m_eModeState == eModeState_Opened && m_pCurMode->m_bReserveClose == true )
	{
		CFadeSystem::GetInst()->StartFade(eFadeStage_Out, m_pCurMode->GetFadeCloseTime() );
		m_pCurMode->m_eModeState = eModeState_Close;
	}
	else if( CFadeSystem::GetInst()->IsPlaying() == false )
	{
		if( m_pCurMode->m_eModeState == eModeState_Open )
		{
			m_pCurMode->m_eModeState = eModeState_Opened;
			m_pCurMode->Opened();
		}
		else if( m_pCurMode->m_eModeState == eModeState_Close )
		{
			m_pCurMode->m_eModeState = eModeState_Closed;
			m_pCurMode->Closed();

			m_pPrevMode = m_pCurMode;
		
			m_pCurMode = m_pNextMode;
			m_pCurMode->Open();
			m_pCurMode->m_eModeState = eModeState_Open;
			CFadeSystem::GetInst()->StartFade(eFadeStage_In, m_pCurMode->GetFadeOpenTime() );
		}
	}
}

void CModeManager::DrawUI()
{
	if( !m_pCurMode ) return;

	if( m_pCurMode->m_eModeState != eModeState_Closed )
		m_pCurMode->DrawUI();
}