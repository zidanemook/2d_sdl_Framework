#pragma once
#include "UIWnd.h"

class CComponent;
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
	virtual void		HandleEvent(SDL_Event& event);

private:
	std::wstring		m_Text;
	SDL_Texture*		m_pTexture;//Font
	SDL_Point			m_FontTextureSize;
	SDL_Color			m_Color;
	CComponent*			m_pIdle_Image;//Button Image
	CComponent*			m_pClicked_Image;
	CComponent*			m_pOnMouse_Image;

	SDL_Rect			m_srcRect;
	SDL_Rect			m_destRect;
public:
	void SetText(const wchar_t* pwszText);
	void SetText(const std::wstring& wstText);
	void SetIdleImage(CComponent* pImage);
	void SetClickedImage(CComponent* pImage);
	void SetOnMouseImage(CComponent* pImage);

	std::wstring& GetText();
};

