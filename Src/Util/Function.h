#ifndef Function_h
#define Function_h

#include "SDL.h"
#include <atlstr.h>

#define MSG_BOX(text) MessageBox(NULL, TEXT(text), NULL, MB_OK)


template <typename T>
void Safe_Delete(T& Pointer)
{
	if (NULL != Pointer)
	{
		delete Pointer;
		Pointer = NULL;
	}
}


template <typename T>
unsigned long Safe_Release(T& pInstance)
{
	unsigned long	dwRefCnt = 0;

	if (NULL != pInstance)
	{
		dwRefCnt = (unsigned long)pInstance->Release();

		if (0 == dwRefCnt)
			pInstance = NULL;
	}

	return dwRefCnt;
}

struct ReleaseMapElement
{
	template<typename T>
	void operator()(T& Element)
	{
		size_t RefCnt = 0;

		RefCnt = Element.second->Release();

		if (0 == RefCnt)
			Element.second = NULL;
	}
};

struct UpdateMapElement
{
	template<typename T>
	void operator()(T& Element)
	{
		Element.second->Update();
	}
};

struct RenderMapElement
{
	template<typename T>
	void operator()(T& Element)
	{
		Element.second->Render();
	}
};

struct ReleaseListElement
{
	template<typename T>
	void operator()(T* Element)
	{
		size_t RefCnt = 0;

		RefCnt = Element->Release();

		if (0 == RefCnt)
			Element = NULL;
	}
};

static bool PointToRectCollision(const SDL_Point& point, const SDL_Rect& rect)
{
	if ((point.x >= rect.x) && (point.x <= (rect.x + rect.w)) &&
		(point.y >= rect.y) && (point.y <= (rect.y + rect.h)))
	{
		return true;
	}
	return false;
}

static bool RectToRectCollision(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;
	}

	return false;
}

static std::string WToM(const wchar_t* wszWide)
{
	int len = WideCharToMultiByte(CP_ACP, 0, wszWide, -1, NULL, 0, NULL, NULL);
	std::string strMulti(len,0);
	WideCharToMultiByte(CP_ACP, 0, wszWide, -1, &strMulti[0], len, NULL, NULL);
	return strMulti;
}

static std::wstring MToW(const char* szMulti)
{
	int nLen = MultiByteToWideChar(CP_ACP, 0, szMulti, (int)strlen(szMulti), NULL, NULL);
	std::wstring wstWide(nLen,0);
	MultiByteToWideChar(CP_ACP, 0, szMulti, (int)strlen(szMulti), &wstWide[0], nLen);
	return wstWide;
}

static void errormsg(const char* szMsg)
{
	char szMessage[1024] = { 0, };
	sprintf_s(szMessage, "%s\n", szMsg);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", szMessage, NULL);
}

static void errormsg(const wchar_t* wszMsg)
{
	char szMessage[1024] = { 0, };
	sprintf_s(szMessage, "%s\n", WToM(wszMsg).c_str());
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", szMessage, NULL);
}




#endif //Function_h