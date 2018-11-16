#pragma once
#include "Component.h"
#include "Vector2D.h"

class CTransform : public CComponent
{
public:
	explicit CTransform();
	~CTransform();

public:
	static CTransform* Create();
	inline virtual	void Free(void);
	void SetPos(const float fX, const float fY);
	void SetPos(const Vector2D& vPos);
	Vector2D* GetPos();

public:

private:
	Vector2D	m_vPos;
};

