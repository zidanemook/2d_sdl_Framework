#pragma once
#include "UIWnd.h"

class CComponent;
class CImageBox : public CUIWnd
{
private:
	explicit CImageBox();
	~CImageBox();

public:
	static CImageBox*	Create();
	inline virtual void Free();
	virtual void		Render();
	void	SetShow(bool bSet);

private:
	CComponent* m_pSingleTexture;

public:
	void SetImage(CComponent* pTexture);


	CComponent* GetImage();
};

