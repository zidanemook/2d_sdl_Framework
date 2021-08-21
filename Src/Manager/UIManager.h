#pragma once
#include "define.h"
#include "json.h"

class CUIWnd;
class CUIMainMenu;
class CUIOption;
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
	CUIWnd* LoadUIFile(const std::wstring& UIFileName);

public:
	void AddUI(std::wstring& Name , CUIWnd* pWnd);
	CUIWnd* ParseUI(Json::Value& value);
	CUIWnd* ParseUIWnd(Json::ValueIterator& iter);
	void ParseCommonAttribute(CUIWnd* pWnd, Json::ValueIterator& iter, eUIType eType);//UI 공통변수 로드
	void ParseImageBox(CUIWnd* pWnd, Json::ValueIterator& iter);
	void ParseTextButton(CUIWnd* pWnd, Json::ValueIterator& iter);
	eUIType StringTypeToEnumType(const wchar_t* wszType);
	eUITextAlignType VerticalAlignStringToEnum(const wchar_t* wszType);
	eUITextAlignType HorizontalAlignStringToEnum(const wchar_t* wszType);
	
public:
	CUIWnd* GetUIWndByName(const std::wstring& Name);
	CUIWnd* GetRootUIWndByName(const std::wstring& Name);
	void AddToRenderList(CUIWnd* pWnd);
	void DeleteFromRenderListByName(const std::wstring& Name);
	void SetFocusWnd(CUIWnd* pWnd);
	CUIWnd* GetFocusWnd();
	void SetPreFocusWnd(CUIWnd* pWnd);
	CUIWnd* GetPreFocusWnd();

public:
	CUIMainMenu*	GetUIMainMenu();
	CUIOption*		GetUIOption();

private:
	std::map<std::wstring, CUIWnd*> m_mapUI;//All UIWnd
	std::map<std::wstring, CUIWnd*> m_mapRootUI;//All rootUIWNd, FileName, RootWnd
	std::list<CUIWnd*> m_listRenderUI;//For Render;


private:
	CUIMainMenu*	m_pUIMainMenu;
	CUIWnd*			m_pFocusedWnd;
	CUIWnd*			m_pPreFocuseWnd;
	CUIOption*		m_pUIOption;
};

#define UIMGR CUIManager::GetInst()