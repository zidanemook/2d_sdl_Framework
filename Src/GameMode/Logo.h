/*!
 * \class CLogo
 *
 * 
 *
 * \brief 
 *
�ΰ� ���

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
class CLogo : public CBaseMode
{
private:
	explicit CLogo();
	~CLogo();

public:
	static CLogo* Create();
	inline virtual void Free();

	void Init();
	virtual void Update();
	virtual void Open();
	virtual void Close();
	virtual void Closed();

private:
	CSingleTexture* m_pLogo;
};

