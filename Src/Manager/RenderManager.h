#pragma once

#include "Base.h"

#define GROUND_RENDER_COUNT	100
#define OBJECT_RENDER_COUNT	100
#define EFFECT_RENDER_COUNT	100
#define UI_RENDER_COUNT		100
#define FADE_RENDER_COUNT	1

class Vector2D;
class CRenderCommand : public CBase
{
protected:
	explicit CRenderCommand();
	~CRenderCommand();

public:
	static CRenderCommand* Create();
	inline virtual void Free(void);

	void Initialize();
	void Set(const tstring& tsName, SDL_Texture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect, eRenderLayer RenderLayer, Vector2D* vpPos, bool* bpShow, SDL_BlendMode* pBlendMode, Uint8* puiAlpha);
	bool IsInUse();
	bool IsShow();
	

	void operator=(CRenderCommand* pRenderCommand);
	//void SetInUse(bool bInuse);

	tstring&		GetName();
	SDL_Texture*	GetTexture();
	SDL_Rect*		GetSrcRect();
	SDL_Rect*		GetDestRect();
	eRenderLayer	GetRenderLayer();
	Vector2D*		GetPos();
	bool*			GetShow();
	SDL_BlendMode*	GetBlendMode();
	Uint8*			GetAlpha();

protected:
	tstring			m_tsName;
	SDL_Texture*	m_pTexture;
	SDL_Rect*		m_pSrcRect;
	SDL_Rect*		m_pDestRect;
	eRenderLayer	m_eRenderLayer;
	bool			m_bIsInUse;
	Vector2D*		m_pvPos;
	bool*			m_pbShow;
	SDL_BlendMode*  m_pBlend;
	Uint8*			m_pAlpha;

	friend class CRenderManager;
};


class CRenderManager
{
private:
	static CRenderManager*		m_pInst;

public:
	static CRenderManager* GetInstance(void)
	{
		if (m_pInst == NULL)
			m_pInst = new CRenderManager;

		return m_pInst;
	}

	void DestroyInstance(void)
	{
		Destroy();
		delete m_pInst;
		m_pInst = NULL;
	}

public:
	CRenderManager();
	~CRenderManager();

public:
	bool Init(SDL_Window * pWindow);
	void RenderClear();
	void RenderPresent();
	void RenderCopy(SDL_Texture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect);
	void Render();
	//Add when to render
	void AddRenderCommand(const tstring& name, SDL_Texture* pTexture, SDL_Rect* pSrcRect, SDL_Rect* pDestRect, eRenderLayer RenderLayer, Vector2D* pvPos, bool* bpShow, SDL_BlendMode* pBlendMode, Uint8* puiAlpha);
	//void DeleteRenderCommand(tstring& name, eRenderLayer RenderLayer);
	void AddEmpty(eRenderLayer eLayer);
	void Destroy();

public:
	SDL_Renderer* GetRenderer();

private:
	SDL_Renderer *m_pRenderer;

	std::vector<CRenderCommand*> m_vRenderCommand[eRenderLayer_Max];

	//Indicates the next element of the last element in use.
	int m_iEmptyIndex[eRenderLayer_Max];// 출력대상중 꼬리에 있는것 다음에 빈곳
};

#define RdrMgr CRenderManager::GetInstance()
#define SDLRdr	RdrMgr->GetRenderer()

