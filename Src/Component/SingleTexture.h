#pragma once
#include "Component.h"
#include "Vector2D.h"

class CTexture;
class CSingleTexture : public CComponent
{
public:
	explicit CSingleTexture();
	~CSingleTexture();

public:
	static CSingleTexture* Create();
	static CSingleTexture* Create(CTexture* pTexture);
	inline virtual void Free(void);
	virtual void Update();

public:
	void Init();
	void SetLayer(eRenderLayer eLayer);
	eRenderLayer GetLayer();
	//void SetTexture(SDL_Texture* pSDLTexture);
	void SetTexture(CTexture* pTexture);
	bool GetShow();
	void SetShow(bool set);
	void Set(SDL_Rect& srcRect, SDL_Rect& destRect, eRenderLayer eLayer, CTexture* pTexture);
	void SetBlendMode(SDL_BlendMode BlendMode);
	void SetAlpha(Uint8 uiAlpha);
	void SetName(wchar_t* pszName);
	void SetName(std::wstring& tstrName);

	CTexture* GetTexture();
	SDL_Rect& GetSrcRect();
	SDL_Rect& GetDestRect();

private:
	eRenderLayer	m_RendereLayer;
	CTexture*		m_pTexture;
	bool			m_bShow;
	SDL_Rect		m_SrcRect;
	SDL_Rect		m_DestRect;
	Vector2D		m_vDestPos;
	SDL_BlendMode	m_BlendMode;
	Uint8			m_uiAlpha;
	std::wstring			m_Name;
};

