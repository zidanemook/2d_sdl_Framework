/*!
 * \class CLogo
 *
 * 
 *
 * \brief 
 *
���θ޴� ���

 * TODO: long description
 *
 * \note 
 *
 * \author mook
 *
 * \version 1.0
 *
 * \date 11�� 2018
 *
 * Contact: user@company.com
 *
 */

#pragma once
#include "BaseMode.h"

class CSingleTexture;
class CMainmenu : public CBaseMode
{
private:
	explicit CMainmenu();
	~CMainmenu();

public:
	static CMainmenu* Create();
	inline virtual void Free(void);

	void Init();
	virtual void Update();
	virtual void Open();
	virtual void Close();
	virtual void Closed();

private:
	CSingleTexture* m_pSkyBg;
};

