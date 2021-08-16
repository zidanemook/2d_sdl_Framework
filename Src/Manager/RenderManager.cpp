#include "stdafx.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Vector2D.h"
#include "Function.h"
#include "ObjMgr.h"
#include "Texture.h"
//nclude "UIManager.h"


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

static bool YSorting(CRenderCommand* Command1, CRenderCommand* Command2)
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
	m_eRenderLayer = eRenderLayer_Ground;
	m_bIsInUse = false;
	m_pvPos = NULL;
	m_pbShow = NULL;
	m_pBlend = NULL;
	m_pAlpha = NULL;
}

void CRenderCommand::Set(const std::wstring& tsName, SDL_Texture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect, eRenderLayer RenderLayer, bool* bpShow, SDL_BlendMode* pBlendMode, Uint8* puiAlpha)
{
	if ( pTexture )
	{
		m_tsName = tsName;
		m_pTexture = pTexture;
		m_pSrcRect = pSrcRect;
		m_pDestRect = pDestRect;
		m_eRenderLayer = RenderLayer;
		m_bIsInUse = true;
		m_pbShow = bpShow;
		m_pBlend = pBlendMode;
		m_pAlpha = puiAlpha;
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

void CRenderCommand::operator=(CRenderCommand* pRenderCommand)
{
	Set(pRenderCommand->GetName(), pRenderCommand->GetTexture(), pRenderCommand->GetSrcRect(), pRenderCommand->GetDestRect(), pRenderCommand->GetRenderLayer(), pRenderCommand->GetShow(), pRenderCommand->GetBlendMode(), pRenderCommand->GetAlpha());
}

//void CRenderCommand::SetInUse(bool bInuse)
//{
//	m_bIsInUse = bInuse;
//}

std::wstring& CRenderCommand::GetName()
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

bool* CRenderCommand::GetShow()
{
	if (m_pbShow)
		return m_pbShow;

	return NULL;
}

SDL_BlendMode* CRenderCommand::GetBlendMode()
{
	return m_pBlend;
}

Uint8* CRenderCommand::GetAlpha()
{
	return m_pAlpha;
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
	bool bResult = false;

	m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer)
	{
		SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
		bResult = true;
	}
	else
		log("SDL_CreateRenderer failed\n");

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
	//RenderClear();
	CRenderCommand* pRenderCommand = NULL;

	for (int i = eRenderLayer::eRenderLayer_Ground; i < eRenderLayer::eRenderLayer_Max; ++i)
	{
		if (i == eRenderLayer_Object)
		{
			m_RenderCommand[i].sort(YSorting);
		}

		for (RENITER iter = m_RenderCommand[i].begin(); iter != m_RenderCommand[i].end(); )
		{
			pRenderCommand = *iter;

			if (pRenderCommand)
			{
				if (pRenderCommand->IsShow())
				{
					SDL_SetTextureBlendMode(pRenderCommand->GetTexture(), *(pRenderCommand->GetBlendMode()));
					SDL_SetTextureAlphaMod(pRenderCommand->GetTexture(), *(pRenderCommand->GetAlpha()));

					SDL_RenderCopy(m_pRenderer, pRenderCommand->GetTexture(), pRenderCommand->GetSrcRect(), pRenderCommand->GetDestRect());
					iter++;
				}
				else
				{
					if (i == eRenderLayer_Object)
						OBJMGR->DeleteProcess((*iter)->GetName());
					//else if()

					iter = m_RenderCommand[i].erase(iter);
				}
					
			}
			else
				iter++;
		}
	}
	

	//RenderPresent();
}

void CRenderManager::AddRenderCommand(const std::wstring& name, CTexture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect, eRenderLayer RenderLayer, bool* bpShow, SDL_BlendMode* pBlendMode, Uint8* puiAlpha)
{
	CRenderCommand* pcommand = new CRenderCommand;

	if (pTexture && false == pTexture->GetLoaded())
	{
		RSCMgr->LoadTexture(pTexture->GetName(), pTexture->GetPath());
	}

	pcommand->Set(name, pTexture->GetTexture(), pSrcRect, pDestRect, RenderLayer, bpShow, pBlendMode, puiAlpha);
	m_RenderCommand[RenderLayer].push_back( pcommand);
}

void CRenderManager::Destroy()
{
	for (int i = eRenderLayer::eRenderLayer_Ground; i < eRenderLayer::eRenderLayer_Max; ++i)
	{
		for_each(m_RenderCommand[i].begin(), m_RenderCommand[i].end(), ReleaseListElement());
		m_RenderCommand[i].clear();
	}
	
}

SDL_Renderer* CRenderManager::GetRenderer()
{
	return m_pRenderer;
}
