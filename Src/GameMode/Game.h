/*!
 * \class CGame
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 게임 플레이 모드

 * TODO: long description
 *
 * \note 
 *
 * \author mook
 *
 * \version 1.0
 *
 * \date 7월 2018
 *
 * Contact: user@company.com
 *
 */

#pragma once
#include "BaseMode.h"

class CGame : public CBaseMode
{
private:
	explicit CGame();
	~CGame();

public:
	static CGame* Create();
	inline virtual void Free(void);

	void Init();
	virtual void Update();

	virtual void Open();
	virtual void Close();
};

