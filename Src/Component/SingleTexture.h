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
	//void SetTexture(SDL_Texture* pSDLTexture);
	void SetTexture(CTexture* pTexture);
	bool GetShow();
	void SetShow(bool set);
	void Set(SDL_Rect& srcRect, SDL_Rect& destRect, CTexture* pTexture);

private:
	CTexture*	m_pTexture;
	bool		m_bShow;
	SDL_Rect	m_SrcRect;
	SDL_Rect	m_DestRect;
	Vector2D	m_vDestPos;
};

