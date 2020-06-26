#pragma once
#include "UIWnd.h"

class CComponent;
class CSingleTexture;
class CTextButton : public CUIWnd
{
private:
	explicit CTextButton();
	~CTextButton();

public:
	static CTextButton* Create();
	inline virtual void Free();

public:
	virtual void		Render();
	//virtual void		HandleEvent(SDL_Event& event);
	virtual void		SetPos(SDL_Point& Point);

	virtual void		OnMouseLeftButtonUp(SDL_Event& event);
	virtual void		OnMouseLeftButtonDown(SDL_Event& event);
	virtual void		OnMouseOver(SDL_Event& event);
	virtual void		OnMouseOut(SDL_Event& event);

private:
	std::wstring		m_Text;
	CSingleTexture*		m_pFontTexture;//Font
	SDL_Point			m_FontTextureSize;
	int					m_iTextSize;
	SDL_Color			m_Color;
	CComponent*			m_pIdle_Image;//Button Image
	CComponent*			m_pClicked_Image;
	CComponent*			m_pOnMouse_Image;
	CSingleTexture*		m_pImageTexture;
	eUITextAlignType	m_VerticalAlign;
	eUITextAlignType	m_HorizontalAlign;
	SDL_Rect			m_FontSrcRect;
	SDL_Rect			m_FontDestRect;

public:
	//void SetText(const wchar_t* pwszText);
	void SetText(const std::wstring& wstText);
	void SetIdleImage(CComponent* pImage);
	void SetClickedImage(CComponent* pImage);
	void SetOnMouseImage(CComponent* pImage);
	void SetTextSize(int iSize);
	void SetVerticalAlign(eUITextAlignType eType);
	void SetHorizontalAlign(eUITextAlignType eType);

	std::wstring& GetText();

public:
	virtual void SetShow(bool bSet);
};

