#include "stdafx.h"
#include "Transform.h"


CTransform::CTransform()
{
}


CTransform::~CTransform()
{
}

CTransform* CTransform::Create()
{
	CTransform*		pInstance = new CTransform;

	if (!pInstance)
	{
		wprintf(L"CTransform::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTransform::Free(void)
{

}

void CTransform::SetPos(const float fX, const float fY)
{
	m_vPos.m_x = fX;
	m_vPos.m_y = fY;
}

void CTransform::SetPos(const Vector2D& vPos)
{
	m_vPos = vPos;
}

Vector2D* CTransform::GetPos()
{
	return &m_vPos;
}
