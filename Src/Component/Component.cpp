#include "stdafx.h"
#include "Component.h"


CComponent::CComponent()
{
	m_eComponentTypes = eComponentTypes_None;
}

CComponent::~CComponent()
{
}

void CComponent::Free()
{

}

void CComponent::Init()
{

}

void CComponent::Update()
{

}

void CComponent::Render()
{
}

void CComponent::SetOwner(CObj* pOwner)
{
	m_pOwner = pOwner;
}

CObj* CComponent::GetOwner()
{
	return m_pOwner;
}

void CComponent::SetComponentType(eComponentTypes eType)
{
	m_eComponentTypes = eType;
}

eComponentTypes CComponent::GetComponentType()
{
	return m_eComponentTypes;
}
