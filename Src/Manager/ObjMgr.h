#pragma once
#include "define.h"

class CObj;
class CObjMgr
{
private:
	static CObjMgr*		m_pInst;
public:
	static CObjMgr* GetInstance(void)
	{
		if (m_pInst == nullptr)
			m_pInst = new CObjMgr;

		return m_pInst;
	}

	void DestroyInstance(void)
	{
		Destroy();

		delete m_pInst;
		m_pInst = nullptr;
	}
public:
	CObjMgr(void);
	~CObjMgr(void);

private:
	std::map<tstring, CObj*>	m_mapObject;
//	std::set<tstring>			m_setDeleteList;

private:
	int				m_NODEID;

public:
	void Initialize();
	void Progress();
	void Destroy();

public:
	void AddObj(tstring& tsName, CObj* pObj);
	void PopObj(tstring& tsName);
//	void ReservePopObj(tstring& tsName);
	void Update();


	/*void AddObj(CObj* pObj, OBJID ID);
	void PopObj(CObj* pObj, OBJID ID);
	CObj* GetObjByID(int index, OBJID ID);
	CObj* GetCollisionObj();
	CObj* GetCollisionUI();
	OBJLIST&	GetNodeList();
	void ClearByOBJEnum(OBJID ID);*/
};

#define OBJMGR CObjMgr::GetInstance()

