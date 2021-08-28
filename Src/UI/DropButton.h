#pragma once
#include "UIWnd.h"
#include "TextButton.h"

class CComponent;
class CSingleTexture;

class CDropButton : public CTextButton
{
private:
	explicit CDropButton();
	~CDropButton();

public:
	static CDropButton* Create();
	inline virtual void Free();

public:
	//virtual functions
	virtual void		Render();
	//virtual void		HandleEvent(SDL_Event& event);
	virtual void		SetShow(bool set);
	virtual void		OnMouseLeftButtonUp(SDL_Event& event);
	virtual void		OnMouseOver(SDL_Event& event);
	virtual void		OnMouseOut(SDL_Event& event);

protected:
	//member vars
	CUIWnd*					m_pSelectedItem;
	CUIWnd*					m_pOnMouseItem;
	bool					m_bShowItems;
	std::vector<CUIWnd*>	m_vecMenuItems;
public:
	//unique functions
	void		AddItem(CUIWnd* pWnd);
	CUIWnd*		GetSelectedItem();
	void		SetShowItems(bool set);
	bool		GetShowItems();
};

