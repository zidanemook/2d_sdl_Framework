#ifndef Function_h
#define Function_h

#include "SDL.h"

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
		dwRefCnt = pInstance->Release();

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

static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB)
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

#endif //Function_h