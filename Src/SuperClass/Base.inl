CBase::CBase(void) 
: m_uiRefCnt(0)
{

}

CBase::~CBase(void)
{

}

size_t CBase::AddRef(void)
{
	return ++m_uiRefCnt;
}

size_t CBase::Release(void)
{
	if(0 == m_uiRefCnt)
	{
		Free();

		delete this;

		return 0;
	}

	return m_uiRefCnt--;
}