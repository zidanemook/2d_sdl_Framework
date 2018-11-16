#pragma once
#include "Unit.h"

class CPlayer : public CUnit
{
private:
	explicit CPlayer();
	~CPlayer();

public:
	static CPlayer* Create();
	inline virtual void Free();

public:
	virtual void Init();
	virtual void Update();

public:
	

private:
};

