#pragma once
#include "Component.h"

typedef struct tagAnimData
{
	int		m_iFramePerSecond;//anim speed
	int		m_iFramePixelSize;//anim horizontal vertical pixel size
	int		m_iFrameTotalCount;//frame count
}stAnimData;

class CTexture;
class CSprite : public CComponent
{
public:
	explicit CSprite();
	~CSprite();

public:
	static CSprite* Create();
	inline virtual void Free(void);
	virtual void Update();

public:
	void Init();
	bool GetShow();
	void SetShow(bool set);
	int	 GetCurrentFrame();
	const stAnimData&	 GetAnimData(eAnimationState eAnimState);

private:
	CTexture*	m_pTexture;

	bool		m_bShow;
	int			m_iCurrentFrame;
	stAnimData	m_Animation[eAnimationState_Max];
};

