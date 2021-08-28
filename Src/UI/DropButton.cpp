#include "stdafx.h"
#include "DropButton.h"

CDropButton::CDropButton()
:m_pSelectedItem(NULL), m_pOnMouseItem(NULL), m_bShowItems(false)
{
	
}

CDropButton::~CDropButton()
{
}

CDropButton* CDropButton::Create()
{
	CDropButton* pInstance = new CDropButton;

	if (!pInstance)
	{
		wprintf(L"CTextButton::Create Failed\n");

		Safe_Release(pInstance);
	}

	return pInstance;
}

inline void CDropButton::Free()
{
}

void CDropButton::Render()
{
	CTextButton::Render();

	/*if (m_bShowItems)
	{
		for (size_t i = 0; i != m_vecMenuItems.size(); ++i)
		{
			m_vecMenuItems[i]->Render();
		}
	}*/

}

//void CDropButton::HandleEvent(SDL_Event& event)
//{
//	SDL_Point point;
//	point.x = event.motion.x;
//	point.y = event.motion.y;
//
//	CUIWnd* pWnd = NULL;
//	for(size_t i = 0; i != m_vecMenuItems.size(); ++i)
//	{
//		pWnd = m_vecMenuItems[i];
//
//		if (PointToRectCollision(point, pWnd->GetDestRect()) && (true == (pWnd->GetShow())))
//		{
//			m_pOnMouseItem = pWnd;
//			pWnd->HandleEvent(event);
//			return;
//		}
//	}
//
//	//CUIWnd::ProcessEvent(event);
//
//	CTextButton::HandleEvent(event);
//}

void CDropButton::SetShow(bool set)
{
	CTextButton::SetShow(set);

	if (m_bShowItems)
	{
		for (size_t i = 0; i != m_vecMenuItems.size(); ++i)
		{
			m_vecMenuItems[i]->SetShow(set);
		}
	}
}

void CDropButton::OnMouseLeftButtonUp(SDL_Event& event)
{
	CTextButton::OnMouseLeftButtonUp(event);
}

void CDropButton::OnMouseOver(SDL_Event& event)
{
	CTextButton::OnMouseOver(event);
}

void CDropButton::OnMouseOut(SDL_Event& event)
{

	CTextButton::OnMouseOut(event);
}

void CDropButton::AddItem(CUIWnd* pWnd)
{
	m_vecMenuItems.push_back(pWnd);
}

CUIWnd* CDropButton::GetSelectedItem()
{
	return m_pSelectedItem;
}

void CDropButton::SetShowItems(bool set)
{
	m_bShowItems = set;
	for (size_t i = 0; i != m_vecMenuItems.size(); ++i)
	{
		m_vecMenuItems[i]->SetShow(set);
	}

}

bool CDropButton::GetShowItems()
{
	return m_bShowItems;
}
