#ifndef Base_h__
#define Base_h__

class CBase
{
protected:
	inline explicit CBase(void);
	inline virtual ~CBase(void);

public:
	inline size_t	AddRef(void);
	inline size_t	Release(void);

	inline virtual void Free(void) = 0;

private:
	size_t				m_uiRefCnt;

};

#include "Base.inl"

#endif // Base_h__
