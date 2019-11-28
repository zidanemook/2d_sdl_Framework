#pragma once
#include "define.h"
#include "json.h"

class CUIWnd;
class CUIManager
{
private:
	static CUIManager* m_pInst;

public:
	static CUIManager* GetInst(void)
	{
		if (m_pInst == NULL)
			m_pInst = new CUIManager;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}
public:
	CUIManager(void);
	~CUIManager(void);

public:
	void Update();
	void HandleEvent(SDL_Event& event);
	void Render();

public:
	void AddUI(std::wstring& Name , CUIWnd* pWnd);
	void ParseUI(Json::Value& value);
	CUIWnd* ParseUIWnd(Json::ValueIterator& iter);
	void ParseCommonAttribute(CUIWnd* pWnd, Json::ValueIterator& iter, eUIType eType);//UI 공통변수 로드
	void ParseImageBox(CUIWnd* pWnd, Json::ValueIterator& iter);
	void ParseTextButton(CUIWnd* pWnd, Json::ValueIterator& iter);
	eUIType StringTypeToEnumType(const wchar_t* tszType);

public:
	CUIWnd* GetUIWndByName(std::wstring& Name);

private:
	std::map<std::wstring, CUIWnd*> m_mapUI;//All UIWnd
	std::map<std::wstring, CUIWnd*> m_mapRootUI;//All rootUIWNd
	std::list<CUIWnd*> m_listRenderUI;//For Render;
};

#define UIMGR CUIManager::GetInst()