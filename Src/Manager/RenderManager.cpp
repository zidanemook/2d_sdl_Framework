#include "stdafx.h"
#include "RenderManager.h"
#include "Vector2D.h"
#include "Function.h"

//struct RenderFunc
//{
//	template<typename T>
//	void operator()(T* Element)
//	{
//		if( true == Element->IsInUse() )
//			SDL_RenderCopy(SDLRdr, Element->GetTexture(), Element->GetSrcRect(), Element->GetDestRect());
//
//		if( true == Element->ShouldDelete())
//
//	}
//};

bool YSorting(CRenderCommand* Command1, CRenderCommand* Command2)
{
	if (Command1 && Command2 && Command1->GetPos() && Command2->GetPos())
		return Command1->GetPos()->m_y < Command2->GetPos()->m_y ? true : false;

	return false;
}

CRenderCommand::CRenderCommand()
{
	Initialize();
}

CRenderCommand::~CRenderCommand()
{
}


CRenderCommand* CRenderCommand::Create()
{
	CRenderCommand*		pInstance = new CRenderCommand;

	if (!pInstance)
	{
		wprintf(L"CRenderCommand::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRenderCommand::Free(void)
{
	Initialize();
}

void CRenderCommand::Initialize()
{
	m_tsName.clear();
	m_pTexture = nullptr;
	m_pSrcRect = nullptr;
	m_pDestRect = nullptr;
	m_eRenderLayer = eRenderLayer_None;
	m_bIsInUse = false;
	m_pvPos = NULL;
	m_pbShow = NULL;
	
}

void CRenderCommand::Set(const tstring& tsName, SDL_Texture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect, eRenderLayer RenderLayer, Vector2D* vpPos, bool* bpShow)
{
	if ( pTexture && ( eRenderLayer_None != RenderLayer) )
	{
		m_tsName = tsName;
		m_pTexture = pTexture;
		m_pSrcRect = pSrcRect;
		m_pDestRect = pDestRect;
		m_eRenderLayer = RenderLayer;
		m_bIsInUse = true;
		m_pbShow = bpShow;
	}
}

bool CRenderCommand::IsInUse()
{
	return m_bIsInUse;
}

bool CRenderCommand::IsShow()
{
	if (m_pbShow)
		return *m_pbShow;

	return true;
}

bool* CRenderCommand::GetShow()
{
	if (m_pbShow)
		return m_pbShow;

	return NULL;
}

void CRenderCommand::operator=(CRenderCommand* pRenderCommand)
{
	Set(pRenderCommand->GetName(), pRenderCommand->GetTexture(), pRenderCommand->GetSrcRect(), pRenderCommand->GetDestRect(), pRenderCommand->GetRenderLayer(), pRenderCommand->GetPos(),pRenderCommand->GetShow());
}

//void CRenderCommand::SetInUse(bool bInuse)
//{
//	m_bIsInUse = bInuse;
//}

tstring& CRenderCommand::GetName()
{
	return	m_tsName;
}

SDL_Texture* CRenderCommand::GetTexture()
{
	return m_pTexture;
}

SDL_Rect* CRenderCommand::GetSrcRect()
{
	return m_pSrcRect;
}

SDL_Rect* CRenderCommand::GetDestRect()
{
	return m_pDestRect;
}

eRenderLayer CRenderCommand::GetRenderLayer()
{
	return m_eRenderLayer;
}

Vector2D* CRenderCommand::GetPos()
{
	return m_pvPos;
}

//-------------------------------------------------------------------

CRenderManager* CRenderManager::m_pInst = nullptr;

CRenderManager::CRenderManager()
{
}

CRenderManager::~CRenderManager()
{
	SDL_DestroyRenderer(m_pRenderer);
}

bool CRenderManager::Init(SDL_Window * pWindow)
{
	for (int i = eRenderLayer_None; i < eRenderLayer_Max; ++i)
		m_iEmptyIndex[i] = 0;

	bool bResult = false;

	m_pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
	if (m_pRenderer)
	{
		SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
		bResult = true;
	}
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Renderer failed", NULL);

	if (true == bResult)
	{
		for (int i = eRenderLayer_None; i < eRenderLayer_Max; ++i)
		{
			if (i == eRenderLayer_Ground)
			{
				for (int j = 0; j < GROUND_RENDER_DEFAULT; ++j)
					(m_vRenderCommand[i]).push_back(CRenderCommand::Create());
			}
			else if (i == eRenderLayer_Object)
			{
				for (int j = 0; j < OBJECT_RENDER_DEFAULT; ++j)
					(m_vRenderCommand[i]).push_back(CRenderCommand::Create());
			}
			else if (i == eRenderLayer_Effect)
			{
				for (int j = 0; j < EFFECT_RENDER_DEFAULT; ++j)
					(m_vRenderCommand[i]).push_back(CRenderCommand::Create());
			}
			else if (i == eRenderLayer_UI)
				for (int j = 0; j < UI_RENDER_DEFAULT; ++j)
					(m_vRenderCommand[i]).push_back(CRenderCommand::Create());
			
		}
		
	}


	return bResult;
}

void CRenderManager::RenderClear()
{
	SDL_RenderClear(m_pRenderer);
}

void CRenderManager::RenderPresent()
{
	SDL_RenderPresent(m_pRenderer);
}

void CRenderManager::RenderCopy(SDL_Texture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect)
{
	SDL_RenderCopy(m_pRenderer, pTexture, pSrcRect, pDestRect);
}

void CRenderManager::Render()
{
	RenderClear();
	CRenderCommand* pRenderCommand = NULL;

	for (int Layer = 0; Layer < eRenderLayer_Max; ++Layer)
	{
		if(eRenderLayer_Object == Layer )
			std::sort((m_vRenderCommand[Layer]).begin(), (m_vRenderCommand[Layer]).end(), YSorting);

		for (size_t i = 0; i != (m_vRenderCommand[Layer]).size(); ++i)
		{
			pRenderCommand = m_vRenderCommand[Layer][i];
			if (pRenderCommand)
			{
				if (true == pRenderCommand->IsInUse())
				{
					if (false == pRenderCommand->IsShow() || (NULL == pRenderCommand->GetTexture()))
					{
						int iTailIndex = (m_iEmptyIndex[Layer] - 1);
						if (0 > iTailIndex)
							iTailIndex = 0;

						pRenderCommand = m_vRenderCommand[Layer][iTailIndex];
						m_vRenderCommand[Layer][iTailIndex]->Initialize();
						(m_iEmptyIndex[Layer])--;
					}
					else
					{
						SDL_RenderCopy(SDLRdr, pRenderCommand->GetTexture(), pRenderCommand->GetSrcRect(), pRenderCommand->GetDestRect());
					}
				}
			}
		}
	}

	RenderPresent();
}

void CRenderManager::AddRenderCommand(const tstring& name, SDL_Texture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect, eRenderLayer RenderLayer, Vector2D* pvPos, bool* bpShow)
{
	if (true == (m_vRenderCommand[RenderLayer]).empty())
		return;

	if (false == m_vRenderCommand[RenderLayer][m_iEmptyIndex[RenderLayer]]->IsInUse())
	{
		m_vRenderCommand[RenderLayer][m_iEmptyIndex[RenderLayer]]->Set(name, pTexture, pSrcRect, pDestRect, RenderLayer, pvPos,bpShow);
		m_iEmptyIndex[RenderLayer]++;
		if ((int)(m_vRenderCommand[RenderLayer]).size() <= m_iEmptyIndex[RenderLayer])
			AddEmpty(RenderLayer);
	}
	else
	{
		wprintf(L"CRenderManager::AddRenderCommand RenderLayer: %d EmptyIndex: %d vectorsize: %d Failed\n", RenderLayer, m_iEmptyIndex[RenderLayer], (m_vRenderCommand[RenderLayer]).size());
	}
}

//void CRenderManager::DeleteRenderCommand(tstring& name, eRenderLayer RenderLayer)
//{
//	bool bResult = false;
//	int iTailIndex = (m_iEmptyIndex[RenderLayer] - 1);//
//	for (size_t i = 0; (m_vRenderCommand[RenderLayer]).size(); ++i)//이부분 어떻게 최적화??
//	{
//		if ( name == m_vRenderCommand[RenderLayer][i]->GetName() )
//		{
//			m_vRenderCommand[RenderLayer][i] = m_vRenderCommand[RenderLayer][iTailIndex];
//			m_vRenderCommand[RenderLayer][iTailIndex]->Initialize();
//			(m_iEmptyIndex[RenderLayer])--;
//			bResult = true;
//			break;
//		}
//	}
//
//	if (false == bResult)
//		wprintf(L"DeleteRenderCommand failed name: %s layer: %d \n", name.c_str(), RenderLayer);
//	//
//}

void CRenderManager::AddEmpty(eRenderLayer eLayer)
{
	(m_vRenderCommand[eLayer]).push_back(CRenderCommand::Create());
	m_iEmptyIndex[eLayer]++;
	wprintf(L"AddEmpty size: %d layer: %d\n", (m_vRenderCommand[eLayer]).size(), eLayer);
}

void CRenderManager::Destroy()
{
	for (int i = eRenderLayer_None; i < eRenderLayer_Max; ++i)
	{
		for_each(m_vRenderCommand[i].begin(), m_vRenderCommand[i].end(), ReleaseListElement());
		m_vRenderCommand[i].clear();
	}
}

SDL_Renderer* CRenderManager::GetRenderer()
{
	return m_pRenderer;
}
