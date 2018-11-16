#pragma once
#include "BaseMode.h"

class CObj;
class CComponent : public CBase
{
protected:
	explicit CComponent();
	~CComponent();

public:
	inline virtual void Free();

public:
	void Init();
	virtual void Update();
	virtual void Render();

public:
	void SetOwner(CObj* pOwner);
	CObj* GetOwner();
	void SetComponentType(eComponentTypes eType);
	eComponentTypes GetComponentType();

protected:
	CObj* m_pOwner;

	eComponentTypes m_eComponentTypes;
};

