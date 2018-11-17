//특정 캐릭터에 필요한 애니메이션 좌표, 프레임수, 프레임속도 등 저장 및 출력

#pragma once
#include "Component.h"

typedef struct tagAnimData
{
	int		m_iOriginX;//first frame, left point
	int		m_iOriginY;//first frame, top point
	int		m_iHorizontalFramePixelSize;
	int		m_iVerticalFramePixelSize;//anim vertical pixel size
	int		m_iFrameTotalCount;//frame count
	int		m_iFramePerSecond;//anim speed

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
	void SetAnimData(eAnimationState eAnimState, int iOriginX, int iOriginY, int HorizontalFramePixelSize, int VerticalFramePixelSize,  int iFrameTotalCount, int iFramePerSecond);
	void SetTexture(CTexture* pTexture);
	eAnimationState ToAnimationState(TCHAR* tszAnimState);
	void SetAnimationState(eAnimationState eAnimState);

private:
	CTexture*	m_pTexture;

	bool				m_bShow;
	int					m_iCurrentFrame;
	float				m_fTime;
	stAnimData			m_Animation[eAnimationState_Max];
	eAnimationState		m_eAnimationState;
	SDL_Rect			m_SrcRect;
	SDL_Rect			m_DestRect;
};

