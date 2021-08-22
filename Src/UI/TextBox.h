#pragma once
#include "UIWnd.h"

class CComponent;
class CSingleTexture;
class CTextBox : public CUIWnd
{
private:
	explicit CTextBox();
	~CTextBox();

public:
	static CTextBox* Create();
	inline virtual void Free();

public:
	virtual void Render();
	virtual void SetPos(SDL_Point& Point);

private:
	std::wstring		m_Text;
	CSingleTexture*		m_pFontTexture;//Font
	SDL_Point			m_FontTextureSize;
	int					m_iTextSize;
	SDL_Color			m_Color;
	CSingleTexture*		m_pImageTexture;
	eUITextAlignType	m_VerticalAlign;
	eUITextAlignType	m_HorizontalAlign;
	SDL_Rect			m_FontSrcRect;
	SDL_Rect			m_FontDestRect;

public:
	void SetText(const std::wstring& wstText);
	void SetImage(CComponent* pTexture);
	void SetTextSize(int iSize);
	void SetVerticalAlign(eUITextAlignType eType);
	void SetHorizontalAlign(eUITextAlignType eType);

	CComponent* GetImage();

public:
	virtual void SetShow(bool bSet);
};

