#pragma once
#include "BaseMode.h"
#include "Vector2D.h"

static tstring& ComponentTypeToName(eComponentTypes eType)
{
	tstring componenttypename[eComponentTypes_Max] = { _T(""), _T("Transform"), _T("Sprite"), _T("SingleTexture") };

	if (eType <= eComponentTypes_None || eType >= eComponentTypes_Max)
		return componenttypename[eComponentTypes_None];

	return componenttypename[eType];
}

class CComponent;
class CObj : public CBase
{
protected:
	explicit CObj();
	~CObj();

public:
	inline virtual void Free();

public:
	virtual void	Init();
	virtual void	Update();

public:
	void AddComponent(CComponent* pComponent);
	CComponent* GetComponent(eComponentTypes eType);

public:
	void				SetName(tstring& pszName);
	tstring&			GetName();
	void				SetRenderLayer(eRenderLayer eLayer);
	eRenderLayer		GetRenderLayer();
	void				SetPos(const Vector2D& vPos);
	void				SetPos(const float x, const float y);
	Vector2D*			GetPos();
	void				SetShow(bool bSet);
	bool				GetShow();
	eAnimationState		GetAnimState();
	void				SetAnimState(eAnimationState eState);
	bool				IsDead();
	bool				IsAnimFinish(eAnimationState eState);

protected:
	tstring				m_tsName;
	eRenderLayer		m_eRenderLayer;
	bool				m_bShow;
	eAnimationState		m_eAnimState;

protected:
	//std::map<tstring, CComponent*>	m_mapComponent;
	CComponent*			m_Component[eComponentTypes_Max];
};

