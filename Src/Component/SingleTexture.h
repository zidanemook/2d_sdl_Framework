#pragma once
#include "Component.h"

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

private:
	CTexture*	m_pTexture;
	bool		m_bShow;
};

