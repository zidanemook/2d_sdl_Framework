#include "stdafx.h"
#include "UIManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "../UI/UIWnd.h"
#include "../UI/ImageBox.h"
#include "../UI/TextButton.h"
#include "../UI/UIMainMenu.h"
#include "../UI/UIOption.h"
#include "../UI/UIMessageBox.h"
#include "../UI/TextBox.h"
#include "../Component/SingleTexture.h"

CUIManager* CUIManager::m_pInst = NULL;

CUIManager::CUIManager(void)
{
	m_pUIMainMenu = CUIMainMenu::Create();
	m_pUIOption = CUIOption::Create();
	m_pUIMessageBox = CUIMessageBox::Create();
	m_pFocusedWnd = NULL;
	m_pStickMouseWnd = NULL;
}

CUIManager::~CUIManager(void)
{
	m_pUIMainMenu->Release();
	m_pUIOption->Release();
	m_pUIMessageBox->Release();
}

void CUIManager::Update()
{

}

void CUIManager::HandleEvent(SDL_Event& event)
{
	if (SDL_MOUSEMOTION <= event.type && SDL_MOUSEBUTTONUP >= event.type)
	{
		StciMouseProcess(event);

		SDL_Point point;
		point.x = event.motion.x;
		point.y = event.motion.y;

		std::list<CUIWnd*>::reverse_iterator riter = m_listRenderUI.rbegin();
		for (riter; riter != m_listRenderUI.rend(); ++riter)
		{
			//가장 나중 출력되는 UI Rect 부터 순서대로 충돌하고 있는지 판단
			
			if (PointToRectCollision(point, (*riter)->GetDestRect()))
			{
				(*riter)->HandleEvent(event);
				break;
			}
				
		}
	}
	
}

void CUIManager::Render()
{
	std::list<CUIWnd*>::iterator iter = m_listRenderUI.begin();
	for (iter; iter != m_listRenderUI.end(); ++iter)
	{
		(*iter)->Render();
	}
}

CUIWnd* CUIManager::LoadUIFile(const std::wstring& UIFileName)
{
	//ui파일확인
	if (std::wstring::npos == UIFileName.find(L".json"))
		return NULL;
	
	CUIWnd* newWnd = NULL;
	std::map<std::wstring, CUIWnd*>::iterator iter = m_mapRootUI.find(UIFileName);
	if (m_mapRootUI.end() != iter)
	{
		return iter->second;
	}

	newWnd = RSCMgr->LoadUIJSONFile(UIFileName.c_str());
	if (newWnd)
	{
		m_mapRootUI.insert(make_pair(UIFileName, newWnd));
	}

	return newWnd;
}

void CUIManager::AddUI(std::wstring& Name, CUIWnd* pWnd)
{
	std::map<std::wstring, CUIWnd*>::iterator iterEnd = m_mapUI.end();

	if(iterEnd == m_mapUI.find(Name))
		m_mapUI.insert(make_pair(Name, pWnd));
	else
	{
		log("%s UI NAME Duplicate!!", Name.c_str());
	}
}

CUIWnd* CUIManager::ParseUI(Json::Value& value)
{
	Json::Value root = value["Root"];

	int rootsize = root.size();

	CUIWnd* pWnd = NULL;
	for (Json::ValueIterator it = root.begin(); it != root.end(); ++it)
	{
		if (it->isObject())
		{
			pWnd = ParseUIWnd(it);
			if(pWnd)
				AddUI(pWnd->GetName(), pWnd);
		}
	}

	//find root window in UIFile
	while (pWnd && pWnd->GetParent())
	{
	 	pWnd = pWnd->GetParent();
	}
			
	return pWnd;
	
}

CUIWnd* CUIManager::ParseUIWnd( Json::ValueIterator& iter)
{
	eUIType eType;
	eType = StringTypeToEnumType(MToW((*iter)["UIType"].asString().c_str()).c_str());

	CUIWnd* pWnd = NULL;

	switch (eType)
	{
	case eUIType_ImageBox:
	{
		pWnd = CImageBox::Create();
		ParseCommonAttribute(pWnd, iter, eType);
		ParseImageBox(pWnd, iter);
		break;
	}

	case eUIType_TextButton:
	{
		pWnd = CTextButton::Create();
		ParseCommonAttribute(pWnd, iter, eType);
		ParseTextButton(pWnd, iter);
		break;
	}

	case eUIType_TextBox:
	{
		pWnd = CTextBox::Create();
		ParseCommonAttribute(pWnd, iter, eType);
		ParseTextBox(pWnd, iter);
		break;
	}

	default:
	{
	}

	}

	return pWnd;
}

void CUIManager::ParseCommonAttribute(CUIWnd* pWnd, Json::ValueIterator& iter, eUIType eType)
{
	std::wstring wsName;
	SDL_Point Point;

	CUIWnd* pParent = NULL;
	pParent = GetUIWndByName(MToW(((*iter)["Parent"]).asString().c_str()));
	if (pParent)
	{
		pWnd->SetParent(pParent);
		pParent->AddChildren(pWnd);
	}
		
	
	pWnd->SetUIType(eType);

	//std::wstring temp = MToW(((*iter)["Name"]).asString().c_str());
	//if(!temp.empty())
		wsName = MToW(((*iter)["Name"]).asString().c_str());
	if (wsName.empty())
	{
		if(pParent)
			wsName = pParent->GetName() + _T("_");
		wsName += MToW(((*iter)["UIType"]).asString().c_str());
		wchar_t number[16];
		_itow_s(((*iter)["XPos"]).asInt(), number, 10);
		wsName += _T("_");
		wsName += number;
		_itow_s(((*iter)["YPos"]).asInt(), number, 10);
		wsName += _T("_");
		wsName += number;
	}
	pWnd->SetName(wsName.c_str());


	Point.x = (*iter)["XPos"].asInt();
	Point.y = (*iter)["YPos"].asInt();

	if (pParent)
	{
		pWnd->SetRelativePos(Point);
	}

	pWnd->SetPos(Point);

	SDL_Point sizerate;
	sizerate.x = (*iter)["XRate"].asInt();
	sizerate.y = (*iter)["YRate"].asInt();
	if (sizerate.x != 0 || sizerate.y != 0)
		pWnd->SetSizeRate(sizerate);

	SDL_Point size;
	size.x = (*iter)["XSize"].asInt();
	size.y = (*iter)["YSize"].asInt();
	if (size.x != 0 || size.y != 0)
		pWnd->SetSize(size);


	bool bmovable = (*iter)["movable"].asBool();
	pWnd->SetMovable(bmovable);
}

void CUIManager::ParseImageBox(CUIWnd* pWnd, Json::ValueIterator& iter)
{
	CImageBox* pImageBox = dynamic_cast<CImageBox*>(pWnd);
	std::wstring wsImageName;
	wsImageName = MToW(((*iter)["ImageName"]).asString().c_str());
	pImageBox->SetImage(RSCMgr->GetNamingTextureByName(wsImageName));
}

void CUIManager::ParseTextButton(CUIWnd* pWnd, Json::ValueIterator& iter)
{
	CTextButton* pTextButton = dynamic_cast<CTextButton*>(pWnd);
	std::wstring Button_Idle_ImageName = MToW(((*iter)["Button_Idle_ImageName"]).asString().c_str());
	pTextButton->SetIdleImage(RSCMgr->GetNamingTextureByName(Button_Idle_ImageName));

	std::wstring Button_Clicked_ImageName = MToW(((*iter)["Button_Clicked_ImageName"]).asString().c_str());
	pTextButton->SetClickedImage(RSCMgr->GetNamingTextureByName(Button_Clicked_ImageName));

	std::wstring Button_OnMouse_ImageName = MToW(((*iter)["Button_OnMouse_ImageName"]).asString().c_str());
	pTextButton->SetOnMouseImage(RSCMgr->GetNamingTextureByName(Button_OnMouse_ImageName));

	//std::wstring FontType = MToW(((*iter)["Text"]["FontType"]).asString().c_str());

	int FontSize = ((*iter)["Text"]["FontSize"]).asInt();
	pTextButton->SetTextSize(FontSize);

	std::wstring HorizontalAlign = MToW(((*iter)["Text"]["HorizontalAlign"]).asString().c_str());
	pTextButton->SetHorizontalAlign(HorizontalAlignStringToEnum(HorizontalAlign.c_str()));

	std::wstring VerticalAlign = MToW(((*iter)["Text"]["VerticalAlign"]).asString().c_str());
	pTextButton->SetVerticalAlign(VerticalAlignStringToEnum(VerticalAlign.c_str()));

	std::wstring Text = MToW(((*iter)["Text"]["Text"]).asString().c_str());
	pTextButton->SetText(Text);
}

void CUIManager::ParseTextBox(CUIWnd* pWnd, Json::ValueIterator& iter)
{
	CTextBox* pTextBox = dynamic_cast<CTextBox*>(pWnd);

	std::wstring ImageName = MToW(((*iter)["ImageName"]).asString().c_str());
	pTextBox->SetImage(RSCMgr->GetNamingTextureByName(ImageName));

	//std::wstring FontType = MToW(((*iter)["Text"]["FontType"]).asString().c_str());

	int FontSize = ((*iter)["Text"]["FontSize"]).asInt();
	pTextBox->SetTextSize(FontSize);

	std::wstring HorizontalAlign = MToW(((*iter)["Text"]["HorizontalAlign"]).asString().c_str());
	pTextBox->SetHorizontalAlign(HorizontalAlignStringToEnum(HorizontalAlign.c_str()));

	std::wstring VerticalAlign = MToW(((*iter)["Text"]["VerticalAlign"]).asString().c_str());
	pTextBox->SetVerticalAlign(VerticalAlignStringToEnum(VerticalAlign.c_str()));

	std::wstring Text = MToW(((*iter)["Text"]["Text"]).asString().c_str());
	pTextBox->SetText(Text);
}

eUIType CUIManager::StringTypeToEnumType(const wchar_t* wszType)
{
	eUIType eResult = eUIType_None;

	if (0 == _tcscmp(wszType, _T("ImageBox")))
	{
		eResult = eUIType_ImageBox;
	}
	else if (0 == _tcscmp(wszType, _T("TextButton")))
	{
		eResult = eUIType_TextButton;
	}
	else if (0 == _tcscmp(wszType, _T("TextBox")))
	{
		eResult = eUIType_TextBox;
	}
	else if (0 == _tcscmp(wszType, _T("ListBox")))
	{
		eResult = eUIType_ListBox;
	}

	return eResult;
}

eUITextAlignType CUIManager::VerticalAlignStringToEnum(const wchar_t* wszType)
{
	eUITextAlignType result = eUITextAlignType_Vertical_Center;
	if (0 == _tcscmp(wszType, _T("center")))
	{
		result = eUITextAlignType_Vertical_Center;
	}
	else if (0 == _tcscmp(wszType, _T("left")))
	{
		result = eUITextAlignType_Vertical_Left;
	}
	else if (0 == _tcscmp(wszType, _T("right")))
	{
		result = eUITextAlignType_Vertical_Right;
	}

	return result;
}

eUITextAlignType CUIManager::HorizontalAlignStringToEnum(const wchar_t* wszType)
{
	eUITextAlignType result = eUITextAlignType_Horizontal_Center;
	if (0 == _tcscmp(wszType, _T("center")))
	{
		result = eUITextAlignType_Horizontal_Center;
	}
	else if (0 == _tcscmp(wszType, _T("left")))
	{
		result = eUITextAlignType_Horizontal_Left;
	}
	else if (0 == _tcscmp(wszType, _T("right")))
	{
		result = eUITextAlignType_Horizontal_Right;
	}
	return result;
}

CUIWnd* CUIManager::GetUIWndByName(const std::wstring& Name)
{
	std::map<std::wstring, CUIWnd*>::iterator iter = m_mapUI.find(Name);

	if (iter != m_mapUI.end())
		return iter->second;

	return NULL;
}

CUIWnd* CUIManager::GetRootUIWnd(const std::wstring& FileName)
{
	std::map<std::wstring, CUIWnd*>::iterator iter = m_mapRootUI.find(FileName);

	if (iter != m_mapRootUI.end())
		return iter->second;

	return NULL;
}

void CUIManager::AddToRenderList(CUIWnd* pWnd)
{
	if (pWnd)
	{
		m_listRenderUI.push_back(pWnd);
	}

}

void CUIManager::DeleteFromRenderListByName(const std::wstring& Name)
{
	std::list<CUIWnd*>::iterator iter = m_listRenderUI.begin();

	for (iter; iter != m_listRenderUI.end(); ++iter)
	{
		if (Name == (*iter)->GetName())
		{
			iter = m_listRenderUI.erase(iter);
			break;
		}
	}
}

void CUIManager::SetFocusWnd(CUIWnd* pWnd)
{
	m_pPreFocuseWnd = m_pFocusedWnd;
	m_pFocusedWnd = pWnd;
}

void CUIManager::SetPreFocusWnd(CUIWnd* pWnd)
{
	m_pPreFocuseWnd = pWnd;
}

CUIWnd* CUIManager::GetPreFocusWnd()
{
	return m_pPreFocuseWnd;
}

void CUIManager::SetStickMouseWnd(CUIWnd* pWnd)
{
	m_pStickMouseWnd = pWnd;

	if(pWnd)
	{
		SDL_Point ptMouse;
		SDL_GetMouseState(&ptMouse.x, &ptMouse.y);
		SDL_Point ptWndPos = pWnd->GetPos();

		m_ptDiff.x = ptWndPos.x - ptMouse.x;
		m_ptDiff.y = ptWndPos.y - ptMouse.y;
	}
	else
	{
		m_ptDiff.x = 0;
		m_ptDiff.y = 0;
	}
}

void CUIManager::StciMouseProcess(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION && m_pStickMouseWnd)
	{
		SDL_Point ptMouse;
		SDL_GetMouseState(&ptMouse.x, &ptMouse.y);
		SDL_Point ptWnd;
		ptWnd.x = ptMouse.x + m_ptDiff.x;
		ptWnd.y = ptMouse.y + m_ptDiff.y;

		m_pStickMouseWnd->SetPos(ptWnd);
	}
}

CUIWnd* CUIManager::GetFocusWnd()
{
	return m_pFocusedWnd;
}

CUIMainMenu* CUIManager::GetUIMainMenu()
{
	return m_pUIMainMenu;
}

CUIOption* CUIManager::GetUIOption()
{
	return m_pUIOption;
}

CUIMessageBox* CUIManager::GetUIMessageBox()
{
	return m_pUIMessageBox;
}
