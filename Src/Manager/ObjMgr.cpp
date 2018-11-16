#include "stdafx.h"
#include "function.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr*	CObjMgr::m_pInst = nullptr;

CObjMgr::CObjMgr(void)
{
	Initialize();
	m_NODEID = 1;
}


CObjMgr::~CObjMgr(void)
{
}

void CObjMgr::Initialize()
{
}

void CObjMgr::Progress()
{
	/*for(int i = 0; i < OBJ_END; ++i)
	{
		for(iter = m_List[i].begin(); iter != m_List[i].end(); ++iter)
			(*iter)->Progress();
	}*/
}

void CObjMgr::Destroy()
{
	for_each(m_mapObject.begin(), m_mapObject.end(), ReleaseMapElement());
	m_mapObject.clear();
	/*for(int i = 0; i < OBJ_END; ++i)
	{
		for(iter = m_List[i].begin(); iter != m_List[i].end(); ++iter)
		{
			Safe_Delete(*iter);
		}
		m_List[i].clear();
	}*/
}

void CObjMgr::AddObj(tstring& tsName, CObj* pObj)
{
	m_mapObject.insert(std::make_pair(tsName, pObj));
}

void CObjMgr::PopObj(tstring& tsName)
{
	std::map<tstring, CObj*>::iterator iter;
	iter = m_mapObject.find(tsName);

	if (iter != m_mapObject.end())
	{
		iter->second->SetShow(false);
		iter->second->Release();
		iter = m_mapObject.erase(iter);
	}
}

//void CObjMgr::ReservePopObj(tstring& tsName)
//{
//	m_setDeleteList.insert(tsName);
//}

void CObjMgr::Update()
{
	//for_each(m_mapObject.begin(), m_mapObject.end(), UpdateMapElement());

	std::map<tstring, CObj*>::iterator iter = m_mapObject.begin();
	for (iter; iter != m_mapObject.end(); )
	{
		iter->second->Update();
		if (iter->second->IsDead() && iter->second->IsAnimFinish(eAnimationState_Dead))
		{
			iter->second->SetShow(false);
			iter->second->Release();
			iter = m_mapObject.erase(iter);
		}
		else
			++iter;
	}
}

//void CObjMgr::AddObj( CObj* pObj , OBJID ID)
//{
//	if(ID == OBJ_NODE && pObj->GetInfo()->iID == 0)
//		pObj->GetInfo()->iID = m_NODEID++;
//	
//	m_List[ID].push_back(pObj);
//}
//
//void CObjMgr::PopObj( CObj* pObj, OBJID ID )
//{
//	if( ID != OBJ_NODE )
//		return;
//
//	OBJITER iter;
//	for(iter = m_List[ID].begin(); iter != m_List[ID].end(); ++iter)
//	{
//		if((*iter)->GetInfo()->iID == pObj->GetInfo()->iID)
//		{
//			dynamic_cast<CNode*>(*iter)->SendMyDeathToNeighbor();
//			Safe_Delete((*iter));
//			iter = m_List[ID].erase(iter);
//			break;
//		}
//	}
//}
//
//CObj* CObjMgr::GetObjByID( int index, OBJID ID )
//{
//	OBJITER iter;
//	for(iter = m_List[ID].begin(); iter != m_List[ID].end(); ++iter)
//	{
//		if((*iter)->GetInfo()->iID == index)
//			return (*iter);
//	}
//
//	return NULL;
//}
//
//CObj* CObjMgr::GetCollisionObj()
//{
//	for(iter = m_List[OBJ_NODE].begin(); iter != m_List[OBJ_NODE].end(); ++iter)
//	{
//		if( CCollisionMgr::PointEllipseColl(GetMouse(), (*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, (*iter)->GetInfo()->fCX) )
//		{
//			return (*iter);
//		}
//	}
//	return NULL;
//}
//
//CObj* CObjMgr::GetCollisionUI()
//{
//	for(iter = m_List[OBJ_UI].begin(); iter != m_List[OBJ_UI].end(); ++iter)
//	{
//		if( CCollisionMgr::PointRectColl(GetMouse(), (*iter)->GetInfo()->GetRectInfo() ))
//		{
//			return (*iter);
//		}
//	}
//	return NULL;
//}
//
//OBJLIST& CObjMgr::GetNodeList()
//{
//	return m_List[OBJ_NODE];
//}
//
//void CObjMgr::ClearByOBJEnum( OBJID ID )
//{
//	for(iter = m_List[ID].begin(); iter != m_List[ID].end(); ++iter)
//	{
//		Safe_Delete(*iter);
//	}
//	m_List[ID].clear();
//}
